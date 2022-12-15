#include "../header/EndState.h"

EndState::EndState() {};

void EndState::HandleInput(int x, int y, sf::RectangleShape*& pStartSquare, sf::RectangleShape*& pEndSquare, Node*& pStartNode, Node*& pEndNode, Graph* graph, std::vector<std::vector<sf::RectangleShape>>& squareList) const {

    if (pEndSquare != nullptr)
    {
        pEndSquare->setFillColor(sf::Color::White);
        graph->nodes[y][x]->isWall = false;
    }
    pEndSquare = &squareList[y][x];
    squareList[y][x].setFillColor(sf::Color::Red);
    graph->nodes[y][x]->isWall = false;
    pEndNode = graph->nodes[y][x];

}

EndState::~EndState() {};