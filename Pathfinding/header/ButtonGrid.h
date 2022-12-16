#pragma once
#include "Button.h"
class Grid;

class ButtonGrid : public Button
{
public:
	ButtonGrid(Game& game, Grid& grid, const char* text, float x, float y);

	void processInput() override;

private:
	Grid& m_grid;
};

