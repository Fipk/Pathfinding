#include "../header/Game.h"
#include "../header/GameObject.h"
#include "../header/ButtonGrid.h"
#include "../header/Grid.h"

Game::Game()
{
	m_window = new RenderWindow(sf::VideoMode(1800, 950), "OUR PROJECT");

    if (!m_font.loadFromFile("assets/arial.ttf"))
    {
        // error...
    }
    sf::IntRect rectangle(0, 0, 120, 50);
    if (!m_buttonTexture.loadFromFile("assets/background.png", rectangle))
    {
        // erreur...
    }

    Grid* grid = new Grid(*this, 50, 50);
    ButtonGrid* buttonStart = new ButtonGrid(*this, *grid, "Start", 20, m_window->getSize().y - 100);
    ButtonGrid* buttonEnd = new ButtonGrid(*this, *grid, "End", 180, m_window->getSize().y - 100);
    ButtonGrid* buttonWall = new ButtonGrid(*this, *grid, "Wall", 340, m_window->getSize().y - 100);
    ButtonGrid* buttonCompute = new ButtonGrid(*this, *grid, "Compute", 500, m_window->getSize().y - 100);
    ButtonGrid* buttonRefresh = new ButtonGrid(*this, *grid, "Refresh", 660, m_window->getSize().y - 100);
    ButtonGrid* buttonCheckPoint = new ButtonGrid(*this, *grid, "CheckPoint", 820, m_window->getSize().y - 100);

    m_gameObjects.push_back(grid);
    m_gameObjects.push_back(buttonStart);
    m_gameObjects.push_back(buttonEnd);
    m_gameObjects.push_back(buttonWall);
    m_gameObjects.push_back(buttonCompute);
    m_gameObjects.push_back(buttonRefresh);
    m_gameObjects.push_back(buttonCheckPoint);

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
    while (m_window->isOpen())
    {
        processInput();
        render();
    }
}

void Game::processInput()
{
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

void Game::render()
{
    m_window->clear(sf::Color::Black);

    for (auto gameObject : m_gameObjects)
    {
	    gameObject->render();
    }

    m_window->display();
}
