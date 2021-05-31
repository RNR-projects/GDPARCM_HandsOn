#pragma once
#include "IETThread.h"
#include "AGameObject.h"

class DeleterThread : public IETThread, public AGameObject
{
public:
	DeleterThread(int index);
	~DeleterThread();

	void run() override;
	void stop();

	void processInput(sf::Event event) override;
	void initialize() override;
	void update(sf::Time deltaTime) override;

private:
	int deleterIndex;
	int currentIndex = 0;
	
	bool isRunning = false;

	void determineNextMove();
};

