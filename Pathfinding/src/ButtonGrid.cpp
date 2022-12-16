#include "../header/ButtonGrid.h"

#include "../header/Game.h"
#include "../header/Grid.h"

ButtonGrid::ButtonGrid(Game& game, Grid& grid, const char* text, float x, float y) : Button(game, text, x, y), m_grid(grid)
{
}

void ButtonGrid::processInput()
{
	if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (m_textRect.contains(Mouse::getPosition(*m_game.getWindow()).x, Mouse::getPosition(*m_game.getWindow()).y))
        {
            if (m_text.getString() == "Start" && m_grid.getState() != EditState::Start)
            {
                m_grid.stateStart();
            }
            else if (m_text.getString() == "End" && m_grid.getState() != EditState::End)
            {
                m_grid.stateEnd();
            }
            else if (m_text.getString() == "Wall" && m_grid.getState() != EditState::Wall)
            {
                m_grid.stateWall();
            }
            else if (m_text.getString() == "CheckPoint" && m_grid.getState() != EditState::CheckPoint)
            {
                m_grid.stateCheckPoint();
            }
            else if (m_text.getString() == "Compute")
            {
                m_grid.stateCompute();
            }
            else if (m_text.getString() == "Refresh")
            {
                m_grid.stateRefresh();
            }
            else
            {
	            m_grid.stateDefault();
            }
        }
    }
}
