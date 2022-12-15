#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>

struct Node
{
	int x;
    int y;
    bool isWall ;
    Node* parent;
    int distToTarget = 0, distToOrigin = 0;
	std::vector<Node*> neighbors;
};

class Graph
{
public:
	Graph();

	void AddNode(int x, int y, std::vector<Node*>* nodeList);

	void ClearEdge(int x, int y);
	void AddEdge(int xFrom, int yFrom, int xTo, int yTo);

	~Graph();

	std::vector<std::vector<Node*>> nodes;
};