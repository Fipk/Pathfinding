#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>
#include <array>

void SetupText(sf::Text& startText, sf::Font& font, int x, int y, std::string text, int charSize, sf::Color color)
{
    startText.setFont(font);
    startText.setPosition(x, y);
    startText.setString(text);
    startText.setCharacterSize(charSize);
    startText.setFillColor(color);
}

void GenerateSquareGrid(sf::RenderWindow& window, int xSize, int ySize) {

    std::vector<sf::RectangleShape> squareList;
    squareList.reserve(xSize * ySize);

    sf::RectangleShape square;

    int squareSizeX = floor(window.getSize().x / xSize);
    int squareSizeY = floor((window.getSize().y - 100) / ySize);

    square.setSize(sf::Vector2f(squareSizeX, squareSizeY));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(-2);
    
    
    for (int y = 0; y < ySize; y++)
    {
        for (int x = 0; x <= xSize; x++) {
            square.setPosition(squareSizeX * x, squareSizeY * y);
            squareList.push_back(square);
            window.draw(square);
        }
    }
}

int main()
{
#pragma region Declarations
    sf::RenderWindow window(sf::VideoMode(1000, 800), "OUR PROJECT");
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
    
#pragma endregion Declarations

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
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
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // effacement de la fenêtre en noir
        window.clear(sf::Color::Black);

       
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(50, 50));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(-1);
        rectangle.setPosition(0, 0);

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
        window.draw(rectangle);

        GenerateSquareGrid(window, 15, 15);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}