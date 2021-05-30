#include "BGObject.h"
#include "TextureManager.h"
#include "Game.h"

BGObject::BGObject() : AGameObject("Background")
{
}

BGObject::~BGObject()
{
}

void BGObject::initialize()
{
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
	texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	this->sprite->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 8));
}

void BGObject::processInput(sf::Event event)
{
}

void BGObject::update(sf::Time deltaTime)
{
}
