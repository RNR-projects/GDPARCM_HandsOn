#include "SearcherThread.h"
#include "IconList.h"
#include "TextureManager.h"
#include "RNGManager.h"
#include "ListEditorsManager.h"

SearcherThread::SearcherThread(int index) : AGameObject("Searcher " + index)
{
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
		determineNextMove();
		IETThread::sleep(200);
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
}

void SearcherThread::update(sf::Time deltaTime)
{
	
}

void SearcherThread::determineNextMove()
{
	int jumps = RNGManager::getInstance()->getRandomNumber(1, 9);
	for (int i = 0; i < jumps; i++)
	{
		int startingIndex = currentIndex;
		while (!ListEditorsManager::getInstance()->isSearcherMoveSafe(currentIndex))
		{
			currentIndex = (currentIndex + 1) % 10;
		}

		currentIndex = (currentIndex + 1) % 10;
		ListEditorsManager::getInstance()->moveSearcherToIndex(startingIndex, currentIndex, this);
		IETThread::sleep(100);
	}
}
