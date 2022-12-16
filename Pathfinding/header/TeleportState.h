#pragma once

#include "EditState.h"

class TeleportState : public Edit
{
public:
	TeleportState();
	~TeleportState();

	void HandleInput(int x, int y, sf::RectangleShape*& pStartSquare, sf::RectangleShape*& pEndSquare, Node*& pStartNode, Node*& pEndNode, Graph* graph, std::vector<std::vector<sf::RectangleShape>>& squareList, std::vector<Node*>& allCheckPoints) const override;

private:

};