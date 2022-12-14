#pragma once
#include "GameObject.h"

class Button : public GameObject
{
public:
	using Texture = sf::Texture;
	using Sprite = sf::Sprite;
	using Text = sf::Text;
	using IntRect = sf::IntRect;
	using Font = sf::Font;
	using Color = sf::Color;

	Button(RenderWindow& window, float x, float y);

	void processInput() override;
	void update() override;
	void render() override;

	void SetupText(std::string text, int charSize, sf::Color color);

private:
	Texture m_texture;
	Sprite m_sprite;
	Text m_text;
	IntRect textRect;
	Font m_font;
};

