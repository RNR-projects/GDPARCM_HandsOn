#include "RNGManager.h"
#include <random>
#include <time.h>
#include "IETSemaphore.h"

RNGManager* RNGManager::sharedInstance = nullptr;

RNGManager* RNGManager::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new RNGManager();
	return sharedInstance;
}

int RNGManager::getRandomNumber(int min, int maxExclusive)
{
	this->mutex->acquire();
	int value = rand() % (maxExclusive - min) + min;
	this->mutex->release();
	return value;
}

RNGManager::RNGManager()
{
	srand(time(NULL));
	this->mutex = new IETSemaphore(1);
}
