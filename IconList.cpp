#include "IconList.h"
#include "IETSemaphore.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "ThreadPool.h"
#include "IconObject.h"

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
	if (this->iconBank.size() >= 10)
	{
		for (int i = 0; i < 10; i++)
		{
			insertObject(i);
		}
	}
	this->newTexMutex->release();
}

bool IconList::isNextIndexPresent(int currentIndex)
{
	if (currentIndex < 9) {
		return this->displayedIcons[currentIndex + 1] != nullptr;
	}
	else
	{
		return this->displayedIcons[0] != nullptr;
	}
}

void IconList::createObject()
{
	String objectName = "Icon_" + std::to_string(this->iconBank.size());
	IconObject* iconObj = new IconObject(objectName, this->iconBank.size());
	this->iconBank.push(iconObj);

	iconObj->setPosition(-100, -100);

	GameObjectManager::getInstance()->addObject(iconObj);
}

void IconList::insertObject(int index)
{
	IconObject* iconObj = this->iconBank.front();
	this->iconBank.pop();
	this->displayedIcons[index] = iconObj;

	iconObj->setPosition(index * 200, 0);
}

void IconList::deleteObject(int index)
{
	IconObject* deletedIcon = this->displayedIcons[index];
	this->iconBank.push(deletedIcon);
	deletedIcon->setPosition(-100, -100);
	
	this->displayedIcons[index] = nullptr;
}
