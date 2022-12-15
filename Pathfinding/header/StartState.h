#pragma once

#include "EditState.h"

class StartState : public Edit
{
public:
	StartState();
	~StartState();

	void HandleInput(int x, int y, sf::RectangleShape*& pStartSquare, sf::RectangleShape*& pEndSquare, Node*& pStartNode, Node*& pEndNode, Graph* graph, std::vector<std::vector<sf::RectangleShape>>& squareList) const override;

private:

};