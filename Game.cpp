#include "Game.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "BGObject.h"
#include "IconList.h"
#include "RNGManager.h"
#include "ListEditorsManager.h"

const float FRAME_RATE = 60.0f;
const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f / FRAME_RATE);

Game::Game() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hands On Exam", sf::Style::Close) {

	this->window.setFramerateLimit(int(FRAME_RATE));
	TextureManager::getInstance()->loadFromAssetList();

	RNGManager::getInstance();
	
	BGObject* bgObject = new BGObject();
	GameObjectManager::getInstance()->addObject(bgObject);

	IconList* iconList = new IconList();
	GameObjectManager::getInstance()->addObject(iconList);

	ListEditorsManager::getInstance()->assignIconList(iconList);
	ListEditorsManager::getInstance()->initialize();
}

void Game::run() {
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	while (this->window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		
		processEvents();
		//update(TIME_PER_FRAME);
		update(sf::seconds(deltaTime));
		render();

		previousTime = currentTime;
	}
}

void Game::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void Game::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void Game::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}