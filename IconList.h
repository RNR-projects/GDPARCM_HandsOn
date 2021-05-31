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

	void insertObject(int index);
	void deleteObject(int index);
	
	bool isIndexPresent(int index);

	bool isIndexMinimumDeleted(int index);
	
private:
	IconObject* displayedIcons[10];
	
	std::queue<IconObject*> iconBank;

	void createObject();

	int getMinimumDeletedCount();
	
	class IETSemaphore* newTexMutex;
	ThreadPool* pool;
};

