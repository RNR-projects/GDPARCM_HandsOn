#include "ListEditorsManager.h"
#include "InserterThread.h"
#include "DeleterThread.h"
#include "SearcherThread.h"
#include "GameObjectManager.h"
#include "IETSemaphore.h"
#include "IconList.h"
#include "RNGManager.h"

ListEditorsManager* ListEditorsManager::sharedInstance = nullptr;

ListEditorsManager* ListEditorsManager::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new ListEditorsManager();
	}
	return sharedInstance;
}

void ListEditorsManager::assignIconList(IconList* list)
{
	this->iconList = list;
}

void ListEditorsManager::initialize()
{
	this->moveMutex = new IETSemaphore(1);
	this->deleteCheckMutex = new IETSemaphore(1);
	this->editListMutex = new IETSemaphore(1);
	this->insertChoiceMutex = new IETSemaphore(1);
	
	for (int i = 0; i < 10; i++)
	{
		this->isIndexBeingRemoved[i] = false;
		this->isIndexBeingInserted[i] = false;
	}

	for (int i = 0; i < numDeleters; i++)
	{
		DeleterThread* deleter = new DeleterThread(i);
		deleters.push_back(deleter);
		GameObjectManager::getInstance()->addObject(deleter);
		editorsAtAPoint[0].push_back(deleter);
		deleter->setPosition(0, editorsAtAPoint[0].size() * 100);
		deleter->start();
	}

	for (int i = 0; i < numInserters; i++)
	{
		InserterThread* inserter = new InserterThread(i);
		inserters.push_back(inserter);
		GameObjectManager::getInstance()->addObject(inserter);
		editorsAtAPoint[0].push_back(inserter);
		inserter->setPosition(0, editorsAtAPoint[0].size() * 100);
		inserter->start();
	}
	
	for (int i = 0; i < numSearchers; i++)
	{
		SearcherThread* searcher = new SearcherThread(i);
		searchers.push_back(searcher);
		GameObjectManager::getInstance()->addObject(searcher);
		searchersAtAPoint[0].push_back(searcher);
		searcher->setPosition(0, (searchersAtAPoint[0].size() + editorsAtAPoint[0].size()) * 100);
		searcher->start();
	}
}

void ListEditorsManager::moveSearcherToIndex(int currentIndex, int newIndex, AGameObject* object)
{
	this->moveMutex->acquire();
	
	searchersAtAPoint[currentIndex].erase(std::remove(searchersAtAPoint[currentIndex].begin(), searchersAtAPoint[currentIndex].end(), object), searchersAtAPoint[currentIndex].end());
	searchersAtAPoint[newIndex].push_back(object);
	object->setPosition(newIndex * 200, (searchersAtAPoint[newIndex].size() + editorsAtAPoint[newIndex].size()) * 100);
	
	this->moveMutex->release();
}

void ListEditorsManager::moveEditorToIndex(int currentIndex, int newIndex, AGameObject* object)
{
	this->moveMutex->acquire();

	editorsAtAPoint[currentIndex].erase(std::remove(editorsAtAPoint[currentIndex].begin(), editorsAtAPoint[currentIndex].end(), object), editorsAtAPoint[currentIndex].end());
	editorsAtAPoint[newIndex].push_back(object);
	object->setPosition(newIndex * 200, editorsAtAPoint[newIndex].size() * 100);

	this->moveMutex->release();
}

bool ListEditorsManager::isSearcherMoveSafe(int index)
{
	deleteCheckMutex->acquire();
	if (!isIndexBeingRemoved[(index + 1) % 10])
	{
		deleteCheckMutex->release();
		return this->iconList->isIndexPresent((index + 1) % 10);
	}
	else
	{
		deleteCheckMutex->release();
		return false;
	}
}

bool ListEditorsManager::isDeleteIndexSafe(int index)
{
	deleteCheckMutex->acquire();
	if (this->iconList->isIndexMinimumDeleted(index) && !isIndexBeingRemoved[index])
	{
		isIndexBeingRemoved[index] = true;
		deleteCheckMutex->release();
		return true;
	}
	else
	{
		deleteCheckMutex->release();
		return false;
	}
}

int ListEditorsManager::getEmptyIndex()
{
	insertChoiceMutex->acquire();
	std::vector<int> emptyIndices = this->iconList->getEmptyIndices();
	if (!areAllIndicesReserved(emptyIndices)) {
		int index;
		do {
			index = RNGManager::getInstance()->getRandomNumber(0, emptyIndices.size());
		} while (isIndexBeingInserted[emptyIndices[index]]);

		isIndexBeingInserted[emptyIndices[index]] = true;
		
		insertChoiceMutex->release();
		return emptyIndices[index];
	}
	else
	{
		insertChoiceMutex->release();

		return -1;
	}
}

void ListEditorsManager::insertAtIndex(int index)
{
	editListMutex->acquire();
	this->iconList->insertObject(index);

	insertChoiceMutex->acquire();
	isIndexBeingInserted[index] = false;
	
	insertChoiceMutex->release();
	editListMutex->release();
}

void ListEditorsManager::deleteAtIndex(int index)
{
	editListMutex->acquire();
	this->iconList->deleteObject(index);
	
	deleteCheckMutex->acquire();
	isIndexBeingRemoved[index] = false;
	
	deleteCheckMutex->release();
	editListMutex->release();
}

ListEditorsManager::ListEditorsManager()
{
	
}

bool ListEditorsManager::areAllIndicesReserved(std::vector<int> indices)
{
	for (int i = 0; i < indices.size(); i++)
	{
		if (!isIndexBeingInserted[indices[i]])
			return false;
	}
	return true;
}
