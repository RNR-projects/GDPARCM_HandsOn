#include "IconList.h"
#include "IETSemaphore.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "ThreadPool.h"
#include "IconObject.h"
#include <iostream>

IconList::IconList() : AGameObject("iconList")
{
	
}

IconList::~IconList()
{
	delete[] displayedIcons;
	delete this->newTexMutex;
}

void IconList::initialize()
{
	this->newTexMutex = new IETSemaphore(1);
	this->pool = new ThreadPool("pool", 10);
	this->pool->startScheduler();
	for (int i = 0; i < 10; i++)
	{
		this->displayedIcons[i] = nullptr;
	}
	
	for (int i = 0; i < TextureManager::getInstance()->streamingAssetCount; i++)
	{
		TextureManager::getInstance()->loadSingleStreamAsset(i, this, this->pool);
	}
}

void IconList::processInput(sf::Event event)
{
}

void IconList::update(sf::Time deltaTime)
{
}

void IconList::OnFinishedExecution()
{
	this->newTexMutex->acquire();

	createObject();
	if (this->iconBank.size() == 20)
	{
		for (int i = 0; i < 10; i++)
		{
			insertObject(i);
		}
	}
	this->newTexMutex->release();
}

bool IconList::isIndexPresent(int index)
{
	return this->displayedIcons[index] != nullptr;
}

bool IconList::isIndexMinimumDeleted(int index)
{
	if (this->displayedIcons[index] != nullptr)
	{
		return this->displayedIcons[index]->getTimesDeleted() == getMinimumDeletedCount();
	}
	else
		return false;
}

std::vector<int> IconList::getEmptyIndices()
{
	std::vector<int> indices;
	for (int i = 0; i < 10; i++)
	{
		if (displayedIcons[i] == nullptr)
			indices.push_back(i);
	}
	return indices;
}

void IconList::createObject()
{
	String objectName = "Icon " + std::to_string(this->iconBank.size());
	IconObject* iconObj = new IconObject(objectName, this->iconBank.size());
	this->iconBank.push(iconObj);

	iconObj->setPosition(-100, -100);

	GameObjectManager::getInstance()->addObject(iconObj);
}

int IconList::getMinimumDeletedCount()
{
	int minimum = INT_MAX;
	for (int i = 0; i < 10; i++)
	{
		if (displayedIcons[i] != nullptr)
		{
			if (displayedIcons[i]->getTimesDeleted() < minimum)
			{
				minimum = displayedIcons[i]->getTimesDeleted();
			}
		}
	}

	return minimum;
}

void IconList::insertObject(int index)
{
	IconObject* iconObj = this->iconBank.front();
	this->iconBank.pop();
	this->displayedIcons[index] = iconObj;

	iconObj->setPosition(index * 200, 0);

	std::cout << "inserting " << iconObj->getName() << std::endl;
}

void IconList::deleteObject(int index)
{
	IconObject* deletedIcon = this->displayedIcons[index];
	this->iconBank.push(deletedIcon);
	deletedIcon->setPosition(-100, -100);
	this->displayedIcons[index] = nullptr;

	std::cout << "deleting " << deletedIcon->getName() << std::endl;
}
