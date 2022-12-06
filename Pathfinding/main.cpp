#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
#pragma region Declarations
    sf::RenderWindow window(sf::VideoMode(800, 600), "OUR PROJECT");
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        // error...
    }
    sf::IntRect rectangle(20, 500, 120, 50);
    sf::Texture texture;
    if (!texture.loadFromFile("assets/background.png", rectangle))
    {
        // erreur...
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(20, 500);

    sf::IntRect rectangle2(180, 500, 120, 50);
    sf::Sprite sprite2;
    sprite2.setTexture(texture);
    sprite2.setPosition(180, 500);

    sf::IntRect rectangle3(340, 500, 120, 50);
    sf::Sprite sprite3;
    sprite3.setTexture(texture);
    sprite3.setPosition(340, 500);

    sf::IntRect rectangle4(500, 500, 120, 50);
    sf::Sprite sprite4;
    sprite4.setTexture(texture);
    sprite4.setPosition(500, 500);

    sf::IntRect rectangle5(660, 500, 120, 50);
    sf::Sprite sprite5;
    sprite5.setTexture(texture);
    sprite5.setPosition(660, 500);

    sf::Text text;
    text.setFont(font);
    text.setPosition(60, 510);
    text.setString("Start");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    sf::Text text2;
    text2.setFont(font);
    text2.setPosition(222, 510);
    text2.setString("End");
    text2.setCharacterSize(20);
    text2.setFillColor(sf::Color::White);

    sf::Text text3;
    text3.setFont(font);
    text3.setPosition(381, 510);
    text3.setString("Wall");
    text3.setCharacterSize(20);
    text3.setFillColor(sf::Color::White);

    sf::Text text4;
    text4.setFont(font);
    text4.setPosition(520, 510);
    text4.setString("Compute");
    text4.setCharacterSize(20);
    text4.setFillColor(sf::Color::White);

    sf::Text text5;
    text5.setFont(font);
    text5.setPosition(685, 510);
    text5.setString("Refresh");
    text5.setCharacterSize(20);
    text5.setFillColor(sf::Color::White);
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

        // c'est ici qu'on dessine tout
        // window.draw(...);
        window.draw(sprite);
        window.draw(sprite2);
        window.draw(sprite3);
        window.draw(sprite4);
        window.draw(sprite5);
        window.draw(text);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}