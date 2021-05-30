#pragma once
#include "AGameObject.h"
#include <queue>
#include "IExecutionEvent.h"

class IconObject;
class ThreadPool;
class IconList : public AGameObject, IExecutionEvent
{
public:
	IconList();
	~IconList();

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void OnFinishedExecution() override;

	bool isNextIndexPresent(int currentIndex);

private:
	IconObject* displayedIcons[10];
	
	std::queue<IconObject*> iconBank;

	void createObject();
	void insertObject(int index);
	void deleteObject(int index);

	class IETSemaphore* newTexMutex;
	ThreadPool* pool;
};

