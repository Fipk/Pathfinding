#include "../header/DefaultState.h"

DefaultState::DefaultState() {};

void DefaultState::HandleInput(int x, int y, sf::RectangleShape*& pStartSquare, sf::RectangleShape*& pEndSquare, Node*& pStartNode, Node*& pEndNode, Graph* graph, std::vector<std::vector<sf::RectangleShape>>& squareList, std::vector<Node*>& allCheckPoints) const {


    if (pStartNode != graph->nodes[y][x] && pEndNode != graph->nodes[y][x])
    {
        squareList[y][x].setFillColor(sf::Color::White);
        graph->nodes[y][x]->isWall = false;
    }
}

DefaultState::~DefaultState() {};