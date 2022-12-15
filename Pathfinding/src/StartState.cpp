#include "../header/StartState.h"

StartState::StartState() {};

void StartState::HandleInput(int x, int y, sf::RectangleShape*& pStartSquare, sf::RectangleShape*& pEndSquare, Node*& pStartNode, Node*& pEndNode, Graph* graph, std::vector<std::vector<sf::RectangleShape>>& squareList, std::vector<Node*>& allCheckPoints) const {
    
    if (pStartSquare != nullptr)
    {
        pStartSquare->setFillColor(sf::Color::White);
        graph->nodes[y][x]->isWall = false;

    }
    pStartSquare = &squareList[y][x];
    squareList[y][x].setFillColor(sf::Color::Green);
    graph->nodes[y][x]->isWall = false;
    pStartNode = graph->nodes[y][x];


}

StartState::~StartState() {};