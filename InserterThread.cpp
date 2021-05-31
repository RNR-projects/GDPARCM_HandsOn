#include "InserterThread.h"
#include "ListEditorsManager.h"
#include "TextureManager.h"

InserterThread::InserterThread(int index) : AGameObject("Inserter " + index)
{
	this->inserterIndex = index;
}

InserterThread::~InserterThread()
{
}

void InserterThread::run()
{
	isRunning = true;
	srand(time(NULL) + inserterIndex * 333);
	while (isRunning)
	{
		IETThread::sleep(500);
		determineNextMove();
	}
}

void InserterThread::stop()
{
	this->isRunning = false;
}

void InserterThread::processInput(sf::Event event)
{
}

void InserterThread::initialize()
{
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("inserter", 0);
	this->sprite->setTexture(*texture);
}

void InserterThread::update(sf::Time deltaTime)
{
}

void InserterThread::determineNextMove()
{
	int insertIndex = ListEditorsManager::getInstance()->getEmptyIndex();
	if (insertIndex != -1)
	{
		ListEditorsManager::getInstance()->moveEditorToIndex(currentIndex, insertIndex, this);
		currentIndex = insertIndex;
		IETThread::sleep(200);
		ListEditorsManager::getInstance()->insertAtIndex(insertIndex);
	}
}
