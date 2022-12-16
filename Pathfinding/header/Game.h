#pragma once
#include <SFML/Graphics.hpp>
#include "EditState.h"

class GameObject;

class Game
{
public:
	using RenderWindow = sf::RenderWindow;
	using Font = sf::Font;
	using Texture = sf::Texture;
	using GameObjectsList = std::vector<GameObject*>;
	using Event = sf::Event;
	using TextUI = sf::Text;

	Game();
	~Game();

	void gameLoop();

	void processInput();
	void render();

	RenderWindow* getWindow() const { return m_window; }

	Font* getFont() { return &m_font; }

	Texture* getButtonTexture() { return &m_buttonTexture; }

private:
	RenderWindow* m_window;

	Font m_font;
	Texture m_buttonTexture;

	GameObjectsList m_gameObjects;
};

