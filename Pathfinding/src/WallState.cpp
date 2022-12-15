#include "../header/WallState.h"

WallState::WallState() {};


void WallState::HandleInput(int x, int y, sf::RectangleShape*& pStartSquare, sf::RectangleShape*& pEndSquare, Node*& pStartNode, Node*& pEndNode, Graph* graph, std::vector<std::vector<sf::RectangleShape>>& squareList) const{
	if (pStartNode != graph->nodes[y][x] && pEndNode != graph->nodes[y][x])
	{
		squareList[y][x].setFillColor(sf::Color::Yellow);
		graph->nodes[y][x]->isWall = true;
	}
}


WallState::~WallState() {};