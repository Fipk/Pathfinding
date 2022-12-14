#include "../header/Graph.h"

Graph::Graph(){};

void Graph::AddNode(int x, int y, std::vector<Node*>* nodeList) {
	Node* node = new Node{ x, y};
	//nodes[y].push_back(node);
	nodeList->push_back(node);
} 

void Graph::AddEdge(int xFrom, int yFrom, int xTo, int yTo) {
	Node* fromNode = nodes[xFrom][yFrom];
	Node* toNode = nodes[xTo][yTo];
	fromNode->neighbors.push_back(toNode);
}


Graph::~Graph() = default;