#include "../header/Grid.h"
#include "../header/DefaultState.h"
#include "../header/StartState.h"
#include "../header/EndState.h"
#include "../header/WallState.h"
#include "../header/CheckpointState.h"
#include "../header/Game.h"

Grid::Grid(Game& game, int colNumber, int rowNumber) : GameObject(game), m_colNumber(colNumber), m_rowNumber(rowNumber)
{
    m_squareList = GenerateSquareGrid(m_colNumber, m_rowNumber);

	m_state = EditState::Default;
    m_editorState = new DefaultState();
    m_stateText.setFont(*m_game.getFont());
    m_stateText.setPosition(945, m_game.getWindow()->getSize().y - 90);
    m_stateText.setString(editStateName[m_state]);
    m_stateText.setCharacterSize(20);
    m_stateText.setFillColor(sf::Color::White);
}

Grid::~Grid()
{
    delete m_editorState;
    auto wallListCopy = m_wallList;
    for(auto& wall : wallListCopy)
        delete wall;
    delete m_pStartSquare;
    delete m_pEndSquare;
    delete m_pStartNode;
    delete m_pEndNode;
    auto allCheckPointsCopy = m_allCheckPoints;
    for(auto& checkPoint : allCheckPointsCopy)
        delete checkPoint;
    auto allPathCopy = m_allPath;
    for(auto& path : allPathCopy)
        for(auto& node : path)
            delete node;
    auto pathToGoalCopy = m_pathToGoal;
    for(auto& path : pathToGoalCopy)
        delete path;
}

void Grid::processInput()
{
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        for (int y = 0; y < m_squareList.size(); y++) {
            for (int x = 0; x < m_squareList[y].size(); x++) {
                if (m_squareList[y][x].getGlobalBounds().contains(Mouse::getPosition(*m_game.getWindow()).x, Mouse::getPosition(*m_game.getWindow()).y))
                {
                m_editorState->HandleInput(x, y, m_pStartSquare, m_pEndSquare, m_pStartNode, m_pEndNode, &m_graph, m_squareList, m_allCheckPoints);

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
}

void Grid::render()
{
    m_game.getWindow()->draw(m_stateText);

    for (int y = 0; y < m_squareList.size(); y++) {
        for (int x = 0; x < m_squareList[y].size(); x++) {
            m_game.getWindow()->draw(m_squareList[y][x]);
        }
    }
}

void Grid::stateStart()
{
    m_editorState = new StartState();
    m_state = EditState::Start;
    m_stateText.setString(editStateName[m_state]);
}

void Grid::stateEnd()
{
    m_editorState = new EndState();
    m_state = EditState::End;
    m_stateText.setString(editStateName[m_state]);
}

void Grid::stateWall()
{
    m_editorState = new WallState();
    m_state = EditState::Wall;
    m_stateText.setString(editStateName[m_state]);
}

void Grid::stateCheckPoint()
{
    m_editorState = new CheckpointState();
    m_state = EditState::CheckPoint;
    m_stateText.setString(editStateName[m_state]);
}

void Grid::stateCompute()
{
    for(auto pathToClean : m_allPath){
        if (!pathToClean.empty())
        {
            for (int i = 1; i < pathToClean.size(); i++)
            {
                if (m_squareList[pathToClean[i]->y][pathToClean[i]->x].getFillColor() == sf::Color::Blue)
                {
                    m_squareList[pathToClean[i]->y][pathToClean[i]->x].setFillColor(sf::Color::White);
                }
            }
        }
    }
    m_allPath.clear();
    
    
    GenerateEdgesOfGraph(m_colNumber, m_rowNumber);
    
    if (!m_allCheckPoints.empty())
    {
        for (int i = 0; i < m_allCheckPoints.size(); i++)
        {
            if (i == 0)
                m_pathToGoal = m_pathfinder.AStar(m_pStartNode, m_allCheckPoints[i]);
            else
                m_pathToGoal = m_pathfinder.AStar(m_allCheckPoints[i-1], m_allCheckPoints[i]);
            m_allPath.push_back(m_pathToGoal);
        }
        m_pathToGoal = m_pathfinder.AStar(m_allCheckPoints[m_allCheckPoints.size() - 1], m_pEndNode);
    } else
    {
        m_pathToGoal = m_pathfinder.AStar(m_pStartNode, m_pEndNode);
    }
    
    
    m_allPath.push_back(m_pathToGoal);
    if (!m_allPath.empty())
    {
        for (int i = 0; i < m_allPath.size() ; i++)
        {
            if (!m_allPath[i].empty())
            {
                for (int j = 1; j < m_allPath[i].size(); j++)
                {
                    m_squareList[m_allPath[i][j]->y][m_allPath[i][j]->x].setFillColor(sf::Color::Blue);
                }
            }
        }
    }
}

void Grid::stateRefresh()
{
    m_state = EditState::Default;
    m_editorState = new DefaultState();

    for (int y = 0; y < m_squareList.size(); y++) {
        for (int x = 0; x < m_squareList[y].size(); x++) {
        
            m_graph.nodes[y][x]->isWall = false;
            m_squareList[y][x].setFillColor(sf::Color::White);

            m_pStartNode = nullptr;
            m_pEndNode = nullptr;

            m_pStartSquare = nullptr;
            m_pEndSquare = nullptr;
            m_allPath.clear();
            m_allCheckPoints.clear();
        }
    }
    m_stateText.setString(editStateName[m_state]);
}

void Grid::stateDefault()
{
    m_editorState = new DefaultState();
    m_state = EditState::Default;
    m_stateText.setString(editStateName[m_state]);
}

std::vector<std::vector<sf::RectangleShape>> Grid::GenerateSquareGrid(int colNumber, int rowNumber)
{
    colNumber = abs(colNumber);
    rowNumber = abs(rowNumber);

    std::vector<sf::RectangleShape> colList;
    colList.reserve(colNumber);
    std::vector<std::vector<sf::RectangleShape>> rowList;
    rowList.reserve(rowNumber);

    sf::RectangleShape square;

    int squareSizeX = floor(m_game.getWindow()->getSize().x / colNumber);
    int squareSizeY = floor((m_game.getWindow()->getSize().y - 100) / rowNumber);
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
            m_game.getWindow()->draw(square);
            m_graph.AddNode(x, y, &colNodeList);
        }
        rowList.push_back(colList);
        m_graph.nodes.push_back(colNodeList);
    }

    return rowList;
}

void Grid::GenerateEdgesOfGraph(int colNumber, int rowNumber)
{
    for (int y = 0; y < rowNumber; y++) {
        for (int x = 0; x < colNumber; x++) {

            m_graph.ClearEdge(x, y);

            if (m_graph.nodes[y][x]->isWall == false) {

                if (x > 0 && m_graph.nodes[y][x - 1]->isWall == false) {
                    m_graph.AddEdge(x, y, x - 1, y); 
                }
                if (y > 0 && m_graph.nodes[y - 1][x]->isWall == false) { 
                    m_graph.AddEdge(x, y, x, y - 1); 
                }

                if (x < colNumber - 1 && m_graph.nodes[y][x + 1]->isWall == false) { 
                    m_graph.AddEdge(x, y, x + 1, y); 

                }
                if (y < rowNumber - 1 && m_graph.nodes[y + 1][x]->isWall == false) { 
                    m_graph.AddEdge(x, y, x, y + 1); 

                }

            }
        }
    }
}
