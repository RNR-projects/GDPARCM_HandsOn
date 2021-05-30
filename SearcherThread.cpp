#include "SearcherThread.h"
#include "IconList.h"
#include "TextureManager.h"
#include "RNGManager.h"

SearcherThread::SearcherThread(int index, IconList* list) : AGameObject("Searcher " + index)
{
	this->list = list;
	this->searchIndex = index;
}

SearcherThread::~SearcherThread()
{
}

void SearcherThread::run()
{
	isRunning = true;
	srand(time(NULL) + this->searchIndex);
	while (isRunning)
	{
		IETThread::sleep(500);
		determineNextMove();
	}
}

void SearcherThread::stop()
{
	isRunning = false;
}

void SearcherThread::processInput(sf::Event event)
{
}

void SearcherThread::initialize()
{
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("selector", 0);
	this->sprite->setTexture(*texture);
	//this->currentIndex = RNGManager::getInstance()->getRandomNumber(0, 10);
	this->setPosition(currentIndex * 200, 100 * searchIndex + 100);
}

void SearcherThread::update(sf::Time deltaTime)
{
	
}

void SearcherThread::determineNextMove()
{
	int jumps = RNGManager::getInstance()->getRandomNumber(1, 9);
	for (int i = 0; i < jumps; i++)
	{
		while (!this->list->isNextIndexPresent(currentIndex))
		{
			currentIndex = (currentIndex + 1) % 10;
		}
		currentIndex = (currentIndex + 1) % 10;
		this->setPosition(currentIndex * 200, 100 * searchIndex + 100);
		IETThread::sleep(100);
	}
}
