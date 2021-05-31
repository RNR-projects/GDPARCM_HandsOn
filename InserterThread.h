#pragma once
#include "IETThread.h"
#include "AGameObject.h"

class InserterThread : public IETThread, public AGameObject
{
public:
	InserterThread(int index);
	~InserterThread();

	void run() override;
	void stop();

	void processInput(sf::Event event) override;
	void initialize() override;
	void update(sf::Time deltaTime) override;

private:
	int inserterIndex;
	int currentIndex = 0;

	bool isRunning = false;

	void determineNextMove();
};

