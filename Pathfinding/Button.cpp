#include "Button.h"

Button::Button(RenderWindow& window, float x, float y) : GameObject(window)
{
    textRect = IntRect(x, y, 120, 50);
    if (!m_texture.loadFromFile("assets/background.png", textRect))
    {
        // erreur...
    }
	m_sprite.setTexture(m_texture);
    if (!m_font.loadFromFile("assets/arial.ttf"))
    {
        // error...
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(x, y);
    SetupText("Test", 20, Color::White);
}

void Button::processInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //TODO: Add Input Handler pcq la ouala c'est degeux
        if (textRect.contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y))
        {

            std::cout << "Test";


        }
    }
}

void Button::update()
{
	
}

void Button::render()
{
	m_window.draw(m_sprite);
    m_window.draw(m_text);
}

void Button::SetupText(std::string text, int charSize, Color color)
{
    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setCharacterSize(charSize);
    m_text.setPosition(textRect.left + (textRect.width - m_text.getLocalBounds().width)/2, textRect.top + (textRect.height - m_text.getLocalBounds().height)/2);
    m_text.setFillColor(color);
}
