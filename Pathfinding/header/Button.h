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

	Button(Game& game, const char* text, float x, float y);

	void processInput() override;
	void render() override;

	void setupText(const char* text, int charSize, Color color);

protected:
	Texture m_texture;
	Sprite m_sprite;
	Text m_text;
	IntRect m_textRect;
	Font m_font;
};

