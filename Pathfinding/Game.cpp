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
	// on fait tourner le programme tant que la fen�tre n'a pas �t� ferm�e
    while (m_window->isOpen())
    {
        processInput();
        update();
        render();
    }
}

void Game::processInput()
{
    // on traite tous les �v�nements de la fen�tre qui ont �t� g�n�r�s depuis la derni�re it�ration de la boucle
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
    // effacement de la fen�tre en noir
    m_window->clear(sf::Color::Black);

    for (auto gameObject : m_gameObjects)
    {
	    gameObject->render();
    }

    // fin de la frame courante, affichage de tout ce qu'on a dessin�
    m_window->display();
}
