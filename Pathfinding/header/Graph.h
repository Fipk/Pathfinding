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
    int Score;
	std::vector<Node*> neighbors;
};

class Graph
{
public:
	Graph();

	void AddNode(int x, int y, std::vector<Node*>* nodeList);

	void ClearEdge(int x, int y);
	void AddEdge(int xFrom, int yFrom, int xTo, int yTo);

	//Do it recursivly later
	~Graph();

	std::vector<std::vector<Node*>> nodes;
};