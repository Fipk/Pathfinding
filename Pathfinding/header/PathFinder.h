#pragma once
#include "Graph.h"

class PathFinder
{

private:

	Node* GetLowestScore(std::vector<Node*> openList);

	void RemoveNode(std::vector<Node*>& openList, Node* currentLowest);

	bool CheckIsInList(std::vector<Node*> list, Node* toCheck);

	int GetDistance(Node* nodeA, Node* nodeB);

	void MakeTracePath(Node* start, Node* end);
public:
	PathFinder();
	void AStar(Node* start, Node* end);
	std::vector<Node*> openList;
	std::vector<Node*> closeList;
};

