#include "../header/Graph.h"

Graph::Graph(){};

void Graph::AddNode(int value, sf::RectangleShape* pSquare) {
	Node* node = new Node{ value , pSquare};
	nodes[value] = node;
} 

void Graph::AddEdge(int from, int to) {
	Node* fromNode = nodes[from];
	Node* toNode = nodes[to];
	fromNode->neighbors.push_back(toNode);
}

Graph::~Graph() = default;