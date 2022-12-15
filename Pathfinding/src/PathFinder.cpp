#include "../header/PathFinder.h"
#include <stdlib.h>

PathFinder::PathFinder()
{
	
}
Node* PathFinder::GetLowestScore(std::vector<Node*> openList, Node* current)
{
	for (int i = 0; i < openList.size();i++)
	{
		if (openList[i]->distToOrigin + openList[i]->distToTarget <= current->distToOrigin + current->distToTarget)
		{
			if (openList[i]->distToTarget < current->distToTarget)
				current = openList[i];
		}
	}
	return current;
}

void PathFinder::RemoveNode(Node* currentLowest)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i] == currentLowest)
		{
			openList.erase(openList.begin() + i);
		}
	}
}

bool PathFinder::CheckIsInList(std::vector<Node*> list, Node* toCheck)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == toCheck)
		{
			return true;
		}
	}
	return false;
}

int PathFinder::GetDistance(Node* nodeA, Node* nodeB)
{
	int dstX = abs(nodeA->x - nodeB->x);
	int dstY = abs(nodeA->y - nodeB->y);

	if (dstX > dstY)
		return 14 * dstY + 10 * (dstX - dstY);
	return 14 * dstX + 10 * (dstY - dstX);
}

std::vector<Node*> PathFinder::MakeTracePath(Node* start, Node* end)
{
	std::vector<Node*> path;
	Node* currentNode = end;

	while (currentNode != start) {
		path.push_back(currentNode);
		currentNode = currentNode->parent;
	}
	return path;
}

std::vector<Node*> PathFinder::AStar(Node* start, Node* end)
{
	std::vector<Node*> emptyNodePath;
	openList.clear();
	closeList.clear();

	if (start == nullptr || end == nullptr) {
		return emptyNodePath;
	}

	openList.push_back(start);
	while(!(openList.empty()))
	{
		Node* currentLowest = GetLowestScore(openList, openList[0]);
		RemoveNode(currentLowest);
		closeList.push_back(currentLowest);

		if (currentLowest == end)
		{
			return MakeTracePath(start,end);
		}

		for (int i = 0; i < currentLowest->neighbors.size();i++)
		{

			if (CheckIsInList(closeList,currentLowest->neighbors[i]) || currentLowest->neighbors[i]->isWall) continue;

			const bool isNotInOpenList = !CheckIsInList(openList, currentLowest->neighbors[i]);
			const int newDistToNeighbour = currentLowest->distToOrigin + GetDistance(currentLowest, currentLowest->neighbors[i]);

			if (newDistToNeighbour < currentLowest->neighbors[i]->distToOrigin || isNotInOpenList)
			{
				currentLowest->neighbors[i]->distToOrigin = newDistToNeighbour;
				currentLowest->neighbors[i]->distToTarget = GetDistance(currentLowest->neighbors[i], end);
				currentLowest->neighbors[i]->parent = currentLowest;

				if (isNotInOpenList) 
				{
					openList.push_back(currentLowest->neighbors[i]);
				}
			}
		}
	}
	return emptyNodePath;
}

