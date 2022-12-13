#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>

#include "Graph.h"

void SetupText(sf::Text& startText, sf::Font& font, int x, int y, std::string text, int charSize, sf::Color color)
{
    startText.setFont(font);
    startText.setPosition(x, y);
    startText.setString(text);
    startText.setCharacterSize(charSize);
    startText.setFillColor(color);
}

void GenerateSquareGrid(sf::RenderWindow& window, int colNumber, int rowNumber, std::vector<sf::RectangleShape> &squareList) {

    colNumber = abs(colNumber);
    rowNumber = abs(rowNumber);

    Graph graph;
   
    /*std::vector<sf::RectangleShape> colList;
    colList.reserve(colNumber);
    std::vector<std::vector<sf::RectangleShape>> rowList;
    rowList.reserve(rowNumber);*/

    squareList.reserve(colNumber * rowNumber);

    //rowList.reserve(rowNumber);

    sf::RectangleShape square;

    int squareSizeX = floor(window.getSize().x / colNumber);
    int squareSizeY = floor((window.getSize().y - 100) / rowNumber);

    square.setSize(sf::Vector2f(squareSizeX, squareSizeY));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(-2);
    
    
    /*for (int y = 0; y < rowNumber; y++)
    {
        colList.clear();
        for (int x = 0; x < colNumber; x++) {
            square.setPosition(squareSizeX * x, squareSizeY * y);
            colList.push_back(square);
            window.draw(square);
        }
        rowList.push_back(colList);
    }*/

    int nodeIncrementer = 0;

    for (int y = 0; y < rowNumber; y++)
   {
       for (int x = 0; x < colNumber; x++) {
           square.setPosition(squareSizeX * x, squareSizeY * y);
           squareList.push_back(square);
           graph.AddNode(nodeIncrementer++);
       }
   }
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

    std::vector<sf::RectangleShape> squareList;
    
#pragma endregion Declarations

    //Generation d'une Grid et tous ses élements (TODO: Extract Graph init and filling)
    GenerateSquareGrid(window, 80, 80, squareList);

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //TODO: Add Input Handler pcq la ouala c'est degeux
                if (rectangle.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    std::cout << "Start";
                }
                if (rectangle2.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    std::cout << "End";
                }
                if (rectangle3.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    std::cout << "Wall";
                }
                if (rectangle4.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    std::cout << "Compute";
                }
                if (rectangle5.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    std::cout << "Refresh";
                }
                for (int i = 0; i < squareList.capacity(); i++) {
                    if (squareList[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    {
                        std::cout << i<< std::endl;
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

        for (sf::RectangleShape square : squareList) {
            window.draw(square);
        }


        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}