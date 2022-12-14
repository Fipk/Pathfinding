#pragma once
#include <SFML/Graphics.hpp>

#include "GameObject.h"

class Game
{
public:
	using RenderWindow = sf::RenderWindow;
	using Event = sf::Event;
	using GameObjectsList = std::vector<GameObject*>;

	Game();
	~Game();

	void gameLoop();
	void processInput();
	void update();
	void render();

private:
	RenderWindow* m_window;
	GameObjectsList m_gameObjects;
};