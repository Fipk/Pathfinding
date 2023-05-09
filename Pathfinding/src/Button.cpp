#include "../header/Button.h"

#include "../header/Game.h"

Button::Button(Game& game, const char* text, float x, float y) : GameObject(game)
{
    m_textRect = IntRect(x, y, 120, 40);
    m_sprite.setTexture(*m_game.getButtonTexture());
    m_sprite.setPosition(x, y);
    setupText(text, 20, Color::White);
}

void Button::processInput()
{
	if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (m_textRect.contains(Mouse::getPosition(*m_game.getWindow()).x, Mouse::getPosition(*m_game.getWindow()).y))
        {
            
        }
    }
}

void Button::render()
{
	m_game.getWindow()->draw(m_sprite);
    m_game.getWindow()->draw(m_text);
}

void Button::setupText(const char* text, int charSize, Color color)
{
	m_text.setFont(*m_game.getFont());
    m_text.setString(text);
    m_text.setCharacterSize(charSize);
    m_text.setPosition(m_textRect.left + (m_textRect.width - m_text.getLocalBounds().width)/2, m_textRect.top + (m_textRect.height - m_text.getLocalBounds().height)/2);
    m_text.setFillColor(color);
}
