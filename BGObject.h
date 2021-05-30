#pragma once
#include "AGameObject.h"
class BGObject : public AGameObject
{
public:
	BGObject();
	~BGObject();

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
};

