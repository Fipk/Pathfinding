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

	void AddEdge(int xFrom, int yFrom, int xTo, int yTo);

    ////Afficher le graphe
    //void print() const {
    //    for (const auto& entry : nodes) {
    //        const Node* node = entry.second;
    //        std::cout << node->value << ": [";

    //        for (const Node* neighbor : node->neighbors) {
    //            std::cout << neighbor->value << " ";
    //        }

    //        std::cout << "]" << std::endl;
    //    }
    //}

	//Do it recursivly later
	~Graph();

	std::vector<std::vector<Node*>> nodes;
};