#pragma once
#include "Graph.h"

class PathFinder
{
	PathFinder();

	void AStar(Node* start, Node* end);
	Node* GetLowestScore(std::vector<Node*> openList);
	void RemoveNode(std::vector<Node*>& openList, Node* currentLowest);
public:
	std::vector<Node*> openList;
	std::vector<Node*> closeList;
};

