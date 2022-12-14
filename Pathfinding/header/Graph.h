#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>

struct Node
{
	int value;
    sf::RectangleShape* pSquare;
	std::vector<Node*> neighbors;
};

class Graph
{
public:
	Graph();

	void AddNode(int value, sf::RectangleShape* pSquare);

	void AddEdge(int from, int to);

    //Afficher le graphe
    void print() const {
        for (const auto& entry : nodes) {
            const Node* node = entry.second;
            std::cout << node->value << ": [";

            for (const Node* neighbor : node->neighbors) {
                std::cout << neighbor->value << " ";
            }

            std::cout << "]" << std::endl;
        }
    }

	//Do it recursivly later
	~Graph();

private:
	std::unordered_map<int, Node*> nodes;
};