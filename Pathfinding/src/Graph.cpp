#include "../header/Graph.h"

Graph::Graph(){};

void Graph::AddNode(int x, int y, std::vector<Node*>* nodeList) {
	Node* node = new Node{ x, y};
	nodeList->push_back(node);
} 

void Graph::ClearEdge(int x, int y) {
	nodes[y][x]->neighbors.clear();
}

void Graph::AddEdge(int xFrom, int yFrom, int xTo, int yTo) {
	Node* fromNode = nodes[yFrom][xFrom];
	Node* toNode = nodes[yTo][xTo];

	fromNode->neighbors.push_back(toNode);
}


Graph::~Graph() = default;