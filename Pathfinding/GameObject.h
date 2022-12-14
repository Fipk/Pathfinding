#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	using RenderWindow = sf::RenderWindow;

	GameObject(RenderWindow& renderTarget);

	virtual ~GameObject() = default;

	virtual void processInput();
	virtual void update();
	virtual void render();

protected:
	RenderWindow& m_window;
};
