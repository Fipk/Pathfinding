#include "Game.h"

#include "Button.h"

Game::Game()
{
	m_window = new RenderWindow(sf::VideoMode(800, 600), "OUR PROJECT");

    m_gameObjects.push_back(new Button(*m_window, 20, m_window->getSize().y - 100));

    gameLoop();
}

Game::~Game()
{
    delete m_window;
    auto gameObjectsCopy = m_gameObjects;
    for(auto& gameObject : gameObjectsCopy)
        delete gameObject;
}

void Game::gameLoop()
{
	// on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (m_window->isOpen())
    {
        processInput();
        update();
        render();
    }
}

void Game::processInput()
{
    // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
    Event event;
    while (m_window->pollEvent(event))
    {
	    for (auto gameObject : m_gameObjects)
	    {
		    gameObject->processInput();
	    }
        if (event.type == Event::Closed)
            m_window->close();
    }
}

void Game::update()
{
    for (auto gameObject : m_gameObjects)
    {
	    gameObject->update();
    }
}

void Game::render()
{
    // effacement de la fenêtre en noir
    m_window->clear(sf::Color::Black);

    for (auto gameObject : m_gameObjects)
    {
	    gameObject->render();
    }

    // fin de la frame courante, affichage de tout ce qu'on a dessiné
    m_window->display();
}
