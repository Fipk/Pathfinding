#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>

#include "header/Graph.h"
#include "header/EditState.h"


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

                //INVERSER X ET Y POUR PREND LE NODE COLONNE 3 LIGNE 5 IL FAUT ECRIRE [y = 5][x = 3]
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

    std::cout << "Edges Computed " << nbOfWall << "Wall" << std::endl;
}

int main()
{
#pragma region Declarations
    sf::RenderWindow window(sf::VideoMode(1800, 950), "OUR PROJECT");
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        // error...
    }
    int buttonY = window.getSize().y - 100;

    sf::IntRect rectangle(20, buttonY, 120, 50);
    sf::Texture texture;
    if (!texture.loadFromFile("assets/background.png", rectangle))
    {
        // erreur...
    }

    //TODO: Refacto button creation
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

    //std::vector<sf::RectangleShape> squareList;


    Graph graph;
    
#pragma endregion Declarations

    //Generation d'une Grid et tous ses élements (TODO: Extract Graph init and filling)
    int colNumber = 20;
    int rowNumber = 20;

    std::vector<std::vector<sf::RectangleShape>> squareList = GenerateSquareGrid(window, colNumber, rowNumber, &graph);

    std::vector<sf::RectangleShape*> wallList;

    EditState state = EditState::Default;
    sf::Text stateText;

    sf::RectangleShape* pStartSquare = nullptr;
    sf::RectangleShape* pEndSquare = nullptr;

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        SetupText(stateText, font, 785, buttonY + 10, editStateName[state], 20, sf::Color::White);

        while (window.pollEvent(event))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //TODO: Add Input Handler pcq la ouala c'est degeux
                if (rectangle.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {

                    if (state != EditState::Start)
                    {
                        state = EditState::Start;
                    }
                    else
                    {
                        state = EditState::Default;
                    }

                }
                if (rectangle2.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    if (state != EditState::End)
                    {
                        state = EditState::End;
                    }
                    else
                    {
                        state = EditState::Default;
                    }
                }
                if (rectangle3.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    if (state != EditState::Wall)
                    {
                        state = EditState::Wall;
                    }
                    else
                    {
                        state = EditState::Default;
                    }
                    
                }
                if (rectangle4.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    std::cout << "Compute";
                    GenerateEdgesOfGraph(&graph, colNumber, rowNumber);
                }
                if (rectangle5.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    std::cout << "Refresh";
                    state = EditState::Default;
                }

                for (int y = 0; y < squareList.size(); y++) {
                    for (int x = 0; x < squareList[y].size(); x++) {
                        if (squareList[y][x].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                        {
                            //TODO: Refacto in StateMachine.
                            if (state == EditState::Start) {
                                if (pStartSquare != nullptr)
                                {
                                    pStartSquare->setFillColor(sf::Color::White);
                                    graph.nodes[y][x]->isWall = false;

                                }
                                pStartSquare = &squareList[y][x];
                                squareList[y][x].setFillColor(sf::Color::Green);
                                graph.nodes[y][x]->isWall = false;

                            }else if (state == EditState::End) {
                                if (pEndSquare != nullptr)
                                {
                                    pEndSquare->setFillColor(sf::Color::White);
                                    graph.nodes[y][x]->isWall = false;

                                }
                                pEndSquare = &squareList[y][x];
                                squareList[y][x].setFillColor(sf::Color::Red);
                                graph.nodes[y][x]->isWall = false;

                            }else if (state == EditState::Wall) {
                                squareList[y][x].setFillColor(sf::Color::Yellow);
                                graph.nodes[y][x]->isWall = true;
                            }
                            else {
                                squareList[y][x].setFillColor(sf::Color::White);
                                graph.nodes[y][x]->isWall = false;
                            }
                        }
                    } 
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // effacement de la fenêtre en noir

        //TODO: We don't have to recolor each loop but only on event.
        window.clear(sf::Color::Black);

        // c'est ici qu'on dessine tout
        // window.draw(...);
        window.draw(sprite);
        window.draw(sprite2);
        window.draw(sprite3);
        window.draw(sprite4);
        window.draw(sprite5);
        window.draw(startText);
        window.draw(endText);
        window.draw(wallText);
        window.draw(computeText);
        window.draw(refreshText);
        window.draw(stateText);

        for (int y = 0; y < squareList.size(); y++) {
            for (int x = 0; x < squareList[y].size(); x++) {
                window.draw(squareList[y][x]);
            }
        }


        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}
