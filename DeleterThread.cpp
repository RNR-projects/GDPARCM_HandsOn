#include "DeleterThread.h"
#include <time.h>
#include "RNGManager.h"
#include "ListEditorsManager.h"
#include "TextureManager.h"

DeleterThread::DeleterThread(int index) : AGameObject("Deleter " + index)
{
	this->deleterIndex = index;
}

DeleterThread::~DeleterThread()
{
}

void DeleterThread::run()
{
	isRunning = true;
	srand(time(NULL) + deleterIndex * 100);
	while (isRunning)
	{
		IETThread::sleep(300);
		determineNextMove();
	}
}

void DeleterThread::stop()
{
	this->isRunning = false;
}

void DeleterThread::processInput(sf::Event event)
{
}

void DeleterThread::initialize()
{
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("deleter", 0);
	this->sprite->setTexture(*texture);
}

void DeleterThread::update(sf::Time deltaTime)
{
}

void DeleterThread::determineNextMove()
{
	int random;
	do
	{
		random = RNGManager::getInstance()->getRandomNumber(0, 10);
	} while (!ListEditorsManager::getInstance()->isDeleteIndexSafe(random));

	ListEditorsManager::getInstance()->moveDeleterToIndex(currentIndex, random, this);
	currentIndex = random;

	IETThread::sleep(200);
	ListEditorsManager::getInstance()->deleteAtIndex(currentIndex);
}
