#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>

#include "header/Graph.h"
#include "header/EditState.h"
#include "header/PathFinder.h"

#include "header/DefaultState.h"
#include "header/StartState.h"
#include "header/EndState.h"
#include "header/WallState.h"
#include "header/CheckpointState.h"


void SetupText(sf::Text& startText, sf::Font& font, int x, int y, std::string text, int charSize, sf::Color color)
{
    startText.setFont(font);
    startText.setPosition(x, y);
    startText.setString(text);
    startText.setCharacterSize(charSize);
    startText.setFillColor(color);
}

std::vector<std::vector<sf::RectangleShape>> GenerateSquareGrid(sf::RenderWindow& window, int colNumber, int rowNumber, Graph* graph) {

    colNumber = abs(colNumber);
    rowNumber = abs(rowNumber);

    std::vector<sf::RectangleShape> colList;
    colList.reserve(colNumber);
    std::vector<std::vector<sf::RectangleShape>> rowList;
    rowList.reserve(rowNumber);

    sf::RectangleShape square;

    int squareSizeX = floor(window.getSize().x / colNumber);
    int squareSizeY = floor((window.getSize().y - 100) / rowNumber);
    square.setSize(sf::Vector2f(squareSizeX, squareSizeY));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(-2);

    std::vector<Node*> colNodeList;

    for (int y = 0; y < rowNumber; y++)
    {
        colList.clear();
        colNodeList.clear();
        for (int x = 0; x < colNumber; x++) {
            square.setPosition(squareSizeX * x, squareSizeY * y);
            colList.push_back(square);
            window.draw(square);
            graph->AddNode(x, y, &colNodeList);
        }
        rowList.push_back(colList);
        graph->nodes.push_back(colNodeList);
    }

    return rowList;
}

void GenerateEdgesOfGraph(Graph* graph, int colNumber, int rowNumber) {
    
    int nbOfWall = 0;

    for (int y = 0; y < rowNumber; y++) {
        for (int x = 0; x < colNumber; x++) {

            graph->ClearEdge(x, y);

            if (graph->nodes[y][x]->isWall == false) {

                if (x > 0 && graph->nodes[y][x - 1]->isWall == false) {
                    graph->AddEdge(x, y, x - 1, y); 
                }
                if (y > 0 && graph->nodes[y - 1][x]->isWall == false) { 
                    graph->AddEdge(x, y, x, y - 1); 
                }

                if (x < colNumber - 1 && graph->nodes[y][x + 1]->isWall == false) { 
                    graph->AddEdge(x, y, x + 1, y); 

                }
                if (y < rowNumber - 1 && graph->nodes[y + 1][x]->isWall == false) { 
                    graph->AddEdge(x, y, x, y + 1); 

                }

            }
            else
            {
                nbOfWall++;
            }
        }
    }

}

int main()
{
#pragma region Declarations
    sf::RenderWindow window(sf::VideoMode(1800, 950), "OUR PROJECT");
    sf::Font font;
    if (!font.loadFromFile("../Pathfinding/assets/arial.ttf"))
    {
        // error...
    }
    int buttonY = window.getSize().y - 100;

    sf::IntRect rectangle(20, buttonY, 120, 50);
    sf::Texture texture;
    if (!texture.loadFromFile("../Pathfinding/assets/background.png", rectangle))
    {
        // erreur...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(20, buttonY);

    sf::IntRect rectangle2(180, buttonY, 120, 50);
    sf::Sprite sprite2;
    sprite2.setTexture(texture);
    sprite2.setPosition(180, buttonY);

    sf::IntRect rectangle3(340, buttonY, 120, 50);
    sf::Sprite sprite3;
    sprite3.setTexture(texture);
    sprite3.setPosition(340,buttonY);

    sf::IntRect rectangle4(500, buttonY, 120, 50);
    sf::Sprite sprite4;
    sprite4.setTexture(texture);
    sprite4.setPosition(500, buttonY);

    sf::IntRect rectangle5(660, buttonY, 120, 50);
    sf::Sprite sprite5;
    sprite5.setTexture(texture);
    sprite5.setPosition(660, buttonY);

    sf::IntRect rectangle6(820, buttonY, 120, 50);
    sf::Sprite sprite6;
    sprite6.setTexture(texture);
    sprite6.setPosition(820, buttonY);

    sf::Text startText;
    SetupText(startText, font, 60, buttonY + 10, "Start", 20, sf::Color::White);

    sf::Text endText;
    SetupText(endText, font, 222, buttonY + 10, "End", 20, sf::Color::White);

    sf::Text wallText;
    SetupText(wallText, font, 381, buttonY + 10, "Wall", 20, sf::Color::White);
    
    sf::Text computeText;
    SetupText(computeText, font, 520, buttonY + 10, "Compute", 20, sf::Color::White);

    sf::Text refreshText;
    SetupText(refreshText, font, 685, buttonY + 10, "Refresh", 20, sf::Color::White);

    sf::Text checkPointText;
    SetupText(checkPointText, font, 825, buttonY + 10, "Checkpoint", 20, sf::Color::White);

    int colNumber = 50;
    int rowNumber = 50;

    Graph graph;

    std::vector<std::vector<sf::RectangleShape>> squareList = GenerateSquareGrid(window, colNumber, rowNumber, &graph);

    std::vector<sf::RectangleShape*> wallList;

    EditState state = EditState::Default;
    Edit* editorState = new DefaultState();
    sf::Text stateText;

    sf::RectangleShape* pStartSquare = nullptr;
    sf::RectangleShape* pEndSquare = nullptr;

    Node* pStartNode = nullptr;
    Node* pEndNode = nullptr;

    std::vector<Node*> allCheckPoints;
    std::vector<std::vector<Node*>> allPath;

    PathFinder pathfinder;

    std::vector<Node*> pathToGoal;
    
#pragma endregion Declarations

    while (window.isOpen())
    {
        sf::Event event;
        SetupText(stateText, font, 945, buttonY + 10, editStateName[state], 20, sf::Color::White);

        while (window.pollEvent(event))
        {   
            //Input Handler
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (rectangle.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {

                    if (state != EditState::Start)
                    {
                        editorState = new StartState();
                        state = EditState::Start;
                    }
                    else
                    {
                        editorState = new DefaultState();
                        state = EditState::Default;
                    }

                }
                if (rectangle2.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    if (state != EditState::End)
                    {
                        editorState = new EndState();

                        state = EditState::End;
                    }
                    else
                    {
                        editorState = new DefaultState();

                        state = EditState::Default;
                    }
                }
                if (rectangle3.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    if (state != EditState::Wall)
                    {
                        editorState = new WallState();

                        state = EditState::Wall;
                    }
                    else
                    {
                        editorState = new DefaultState();

                        state = EditState::Default;
                    }
                    
                }
                if (rectangle4.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    for(auto pathToClean : allPath){
                        if (!pathToClean.empty())
                        {
                            for (int i = 1; i < pathToClean.size(); i++)
                            {
                                if (squareList[pathToClean[i]->y][pathToClean[i]->x].getFillColor() == sf::Color::Blue)
                                {
                                    squareList[pathToClean[i]->y][pathToClean[i]->x].setFillColor(sf::Color::White);
                                }
                            }
                        }
                    }
                    allPath.clear();
                    
                    
                    GenerateEdgesOfGraph(&graph, colNumber, rowNumber);
                    
                    if (!allCheckPoints.empty())
                    {
                        for (int i = 0; i < allCheckPoints.size(); i++)
                        {
                            if (i == 0)
                                pathToGoal = pathfinder.AStar(pStartNode, allCheckPoints[i]);
                            else
                                pathToGoal = pathfinder.AStar(allCheckPoints[i-1], allCheckPoints[i]);
                            allPath.push_back(pathToGoal);
                        }
                        pathToGoal = pathfinder.AStar(allCheckPoints[allCheckPoints.size() - 1], pEndNode);
                    } else
                    {
                        pathToGoal = pathfinder.AStar(pStartNode, pEndNode);
                    }

                    allPath.push_back(pathToGoal);
                    if (!allPath.empty())
                    {
                        for (int i = 0; i < allPath.size() ; i++)
                        {
                            if (!allPath[i].empty())
                            {
                                for (int j = 1; j < allPath[i].size(); j++)
                                {
                                    squareList[allPath[i][j]->y][allPath[i][j]->x].setFillColor(sf::Color::Blue);
                                }
                            }
                        }
                    }
                }
                if (rectangle5.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    state = EditState::Default;
                    editorState = new DefaultState();

                    for (int y = 0; y < squareList.size(); y++) {
                        for (int x = 0; x < squareList[y].size(); x++) {
                        
                            graph.nodes[y][x]->isWall = false;
                            squareList[y][x].setFillColor(sf::Color::White);

                            pStartNode = nullptr;
                            pEndNode = nullptr;

                            pStartSquare = nullptr;
                            pEndSquare = nullptr;
                            allPath.clear();
                            allCheckPoints.clear();
                        }
                    }
                }

                if (rectangle6.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    state = EditState::CheckPoint;
                    editorState = new CheckpointState();
                }

                for (int y = 0; y < squareList.size(); y++) {
                    for (int x = 0; x < squareList[y].size(); x++) {
                        if (squareList[y][x].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                        {
                        editorState->HandleInput(x, y, pStartSquare, pEndSquare, pStartNode, pEndNode, &graph, squareList, allCheckPoints);

                        /*else {
                            if (pStartNode != graph.nodes[y][x] && pEndNode != graph.nodes[y][x])
                            {
                                squareList[y][x].setFillColor(sf::Color::White);
                                graph.nodes[y][x]->isWall = false;
                            }
                        }*/
                        }
                    } 
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        window.clear(sf::Color::Black);

        window.draw(sprite);
        window.draw(sprite2);
        window.draw(sprite3);
        window.draw(sprite4);
        window.draw(sprite5);
        window.draw(sprite6);
        window.draw(startText);
        window.draw(endText);
        window.draw(wallText);
        window.draw(computeText);
        window.draw(refreshText);
        window.draw(checkPointText);
        window.draw(stateText);

        for (int y = 0; y < squareList.size(); y++) {
            for (int x = 0; x < squareList[y].size(); x++) {
                window.draw(squareList[y][x]);
            }
        }


        window.display();
    }

    return 0;
}
