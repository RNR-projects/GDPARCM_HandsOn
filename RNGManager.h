#pragma once

class RNGManager
{
public:
	static RNGManager* getInstance();

	int getRandomNumber(int min, int maxExclusive);
private:
	RNGManager();
	RNGManager(RNGManager const&) {};
	RNGManager& operator=(RNGManager const&) {};
	static RNGManager* sharedInstance;

	class IETSemaphore* mutex;
};

