#include "ListEditorsManager.h"
#include "InserterThread.h"
#include "DeleterThread.h"
#include "SearcherThread.h"
#include "GameObjectManager.h"

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
	for (int i = 0; i < numSearchers; i++)
	{
		SearcherThread* searcher = new SearcherThread(i, this->iconList);
		searchers.push_back(searcher);
		GameObjectManager::getInstance()->addObject(searcher);
		searcher->start();
	}
}

ListEditorsManager::ListEditorsManager()
{
	
}
