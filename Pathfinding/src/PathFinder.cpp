#include "../header/PathFinder.h"

PathFinder::PathFinder()
{
	
}
Node* PathFinder::GetLowestScore(std::vector<Node*> openList)
{
	Node* lowestScoreNode;
	for (int i = 0; i < openList.size();i++)
	{
		if (openList[i]->Score < lowestScoreNode->Score)
		{
			lowestScoreNode->Score = openList[i]->Score;
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

void PathFinder::AStar(Node* start, Node* end)
{
	openList.push_back(start);
	while(true)
	{
		// TODO: Make a function that iterate each node in openList
		Node* currentLowest = GetLowestScore(openList);
		RemoveNode(openList, currentLowest);
		closeList.push_back(currentLowest); // add in the close list

		// TODO: Make a function to check
		if (currentLowest == end) return; // if current equal to end then path found

		for (int i = 0; i < currentLowest->neighbors.size();i++)
		{
			//const auto it = std::find_if(closeList.begin(), closeList.end(), [&end](const auto& pNode)
			//{
			//	return pNode == 
			//});
			//if (it) continue;

			if (currentLowest->neighbors[i]) continue;// TODO:Check is in closed

			if (currentLowest->neighbors[i]->Score || currentLowest->neighbors[i]) // check is new path shorter or neighbour is not in openList
			{
				currentLowest->neighbors[i]->Score = 20; // change the score
				// currentLowest->neighbors[i]->parents = currentLowest;
				if (currentLowest->neighbors[i]) //check is not in openList
				{
					openList.push_back(currentLowest->neighbors[i]);
				}
			}
		}
	}
}

