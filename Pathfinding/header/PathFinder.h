#pragma once
#include "Graph.h"

class PathFinder
{

private:

	Node* GetLowestScore(std::vector<Node*> openList, Node* current);

	void RemoveNode(std::vector<Node*>& openList, Node* currentLowest);

	bool CheckIsInList(std::vector<Node*> list, Node* toCheck);

	int GetDistance(Node* nodeA, Node* nodeB);

	std::vector<Node*> MakeTracePath(Node* start, Node* end);
public:
	PathFinder();
	std::vector<Node*> AStar(Node* start, Node* end);

	std::vector<Node*> openList;
	std::vector<Node*> closeList;
};

