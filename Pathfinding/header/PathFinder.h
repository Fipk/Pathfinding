#pragma once
#include "Graph.h"

class PathFinder
{
	PathFinder();
private:
	void AStar(Node* start, Node* end);

	Node* GetLowestScore(std::vector<Node*> openList);

	void RemoveNode(std::vector<Node*>& openList, Node* currentLowest);

	bool CheckIsInList(std::vector<Node*> list, Node* toCheck);

	int GetDistance(Node* nodeA, Node* nodeB);
public:
	std::vector<Node*> openList;
	std::vector<Node*> closeList;
};

