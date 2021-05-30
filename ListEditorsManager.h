#pragma once
#include <vector>

class IconList;
class ListEditorsManager
{
public:
	static ListEditorsManager* getInstance();

	void assignIconList(IconList* list);
	void initialize();
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
};

