#include "LoadAssetTask.h"
#include "TextureManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"

LoadAssetTask::LoadAssetTask(String path, IExecutionEvent* execEvent)
{
	this->path = path;
	this->execEvent = execEvent;
}

LoadAssetTask::~LoadAssetTask()
{
}

void LoadAssetTask::OnStartTask()
{
	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	this->execEvent->OnFinishedExecution();
	
	delete this;
}
