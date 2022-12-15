#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"

enum EditState
{
	Default,
	Start,
	End,
	Wall,
	CheckPoint

};

static const char* editStateName[] = { "Default", "Start", "End", "Wall", "CheckPoint"};

class Edit
{
public:
	virtual ~Edit() = default;
	virtual void HandleInput(int x, int y, sf::RectangleShape* &pStartSquare, sf::RectangleShape* &pEndSquare, Node* &pStartNode, Node* &pEndNode, Graph* graph, std::vector<std::vector<sf::RectangleShape>>& squareList, std::vector<Node*>& allCheckPoints) const = 0;

	//EditState getCurrentState();
	//void setCurrentState(EditState state);

private:
	EditState currentState;
};