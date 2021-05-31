#pragma once
#include "IETThread.h"
#include "AGameObject.h"

class SearcherThread : public IETThread, public AGameObject
{
public:
	SearcherThread(int index);
	~SearcherThread();

	void run() override;
	void stop();

	void processInput(sf::Event event) override;
	void initialize() override;
	void update(sf::Time deltaTime) override;

private:
	int currentIndex = 0;
	int searchIndex;

	bool isRunning = false;

	void determineNextMove();
};

