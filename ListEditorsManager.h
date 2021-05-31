#pragma once
#include <vector>

class IconList;
class IETSemaphore;
class ListEditorsManager
{
public:
	static ListEditorsManager* getInstance();

	void assignIconList(IconList* list);
	void initialize();

	void moveSearcherToIndex(int currentIndex, int newIndex, class AGameObject* object);
	void moveEditorToIndex(int currentIndex, int newIndex, class AGameObject* object);
	
	bool isSearcherMoveSafe(int index);
	bool isDeleteIndexSafe(int index);

	void deleteAtIndex(int index);
private:
	ListEditorsManager();
	ListEditorsManager(ListEditorsManager const&) {};
	ListEditorsManager& operator=(ListEditorsManager const&) {};
	static ListEditorsManager* sharedInstance;

	std::vector<class SearcherThread*> searchers;
	std::vector<class DeleterThread*> deleters;
	std::vector<class InserterThread*> inserters;

	int const numSearchers = 4;
	int const numInserters = 2;
	int const numDeleters = 1;

	IconList* iconList;

	std::vector<class AGameObject*> searchersAtAPoint[10];
	std::vector<class AGameObject*> editorsAtAPoint[10];
	bool isIndexBeingRemoved[10];

	IETSemaphore* moveMutex;
	IETSemaphore* deleteCheckMutex;
	IETSemaphore* editListMutex;
};

