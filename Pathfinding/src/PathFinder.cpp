#include "../header/PathFinder.h"
#include <stdlib.h>

PathFinder::PathFinder()
{
	
}
Node* PathFinder::GetLowestScore(std::vector<Node*> openList)
{
	Node* lowestScoreNode = new Node();
	for (int i = 0; i < openList.size();i++)
	{
		if (openList[i]->distToOrigin + openList[i]->distToTarget < lowestScoreNode->distToOrigin + lowestScoreNode->distToTarget)
		{
			lowestScoreNode->distToOrigin = openList[i]->distToOrigin;
			lowestScoreNode->distToTarget = openList[i]->distToTarget;
		}
	}
	return lowestScoreNode;
}

void PathFinder::RemoveNode(std::vector<Node*>& openList,Node* currentLowest)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i] == currentLowest)
		{
			openList.erase((openList.begin()-1) + i);
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

void PathFinder::AStar(Node* start, Node* end)
{
	openList.push_back(start);
	while(true)
	{
		Node* currentLowest = GetLowestScore(openList);
		RemoveNode(openList, currentLowest);
		closeList.push_back(currentLowest);

		if (currentLowest == end)
		{
			std::cout << "La sortie a été trouvé." << std::endl;
			return;
		}

		for (int i = 0; i < currentLowest->neighbors.size();i++)
		{
			//const auto it = std::find_if(closeList.begin(), closeList.end(), [&end](const auto& pNode)
			//{
			//	return pNode == 
			//});
			//if (it) continue;

			if (CheckIsInList(closeList,currentLowest->neighbors[i]) || currentLowest->neighbors[i]->isWall) continue;


			const int newDistToNeighbour = currentLowest->distToOrigin + GetDistance(currentLowest, currentLowest->neighbors[i]);
			if (newDistToNeighbour < currentLowest->neighbors[i]->distToOrigin || !CheckIsInList(openList,currentLowest->neighbors[i]))
			{
				currentLowest->neighbors[i]->distToOrigin = newDistToNeighbour;
				currentLowest->neighbors[i]->distToTarget = GetDistance(currentLowest->neighbors[i], end);
				currentLowest->neighbors[i]->parent = currentLowest;

				if (!CheckIsInList(openList, currentLowest->neighbors[i])) 
				{
					openList.push_back(currentLowest->neighbors[i]);
				}
			}
		}
	}
}

