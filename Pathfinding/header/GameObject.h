#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameObject
{
public:
	using Mouse = sf::Mouse;

	explicit GameObject(Game& game) : m_game(game) {}
	virtual ~GameObject() = default;

	virtual void processInput() = 0;
	virtual void render() = 0;

protected:
	Game& m_game;
};

