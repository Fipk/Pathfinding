#pragma once

#include "EditState.h"

class CheckpointState : public Edit
{
public:
	CheckpointState();
	~CheckpointState();

	void HandleInput(int x, int y, sf::RectangleShape*& pStartSquare, sf::RectangleShape*& pEndSquare, Node*& pStartNode, Node*& pEndNode, Graph* graph, std::vector<std::vector<sf::RectangleShape>>& squareList, std::vector<Node*>& allCheckPoints) const override;

private:

};