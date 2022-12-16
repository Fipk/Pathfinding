#pragma once
#include "EditState.h"
#include "GameObject.h"
#include "PathFinder.h"
class Edit;

class Grid : public GameObject
{
public:
	using Text = sf::Text;
    using RectangleShape = sf::RectangleShape;

	Grid(Game& game, int colNumber, int rowNumber);
    ~Grid();

	void processInput() override;
	void render() override;

	EditState getState() const { return m_state; }

    void stateStart();
    void stateEnd();
    void stateWall();
    void stateCheckPoint();
    void stateCompute();
    void stateRefresh();
    void stateDefault();

private:
    std::vector<std::vector<sf::RectangleShape>> GenerateSquareGrid(int colNumber, int rowNumber);
    void GenerateEdgesOfGraph(int colNumber, int rowNumber);

	EditState m_state;
	Edit* m_editorState;

	Text m_stateText;

	int m_colNumber = 50;
    int m_rowNumber = 50;

    Graph m_graph;

    std::vector<std::vector<RectangleShape>> m_squareList;

    std::vector<RectangleShape*> m_wallList;

	RectangleShape* m_pStartSquare = nullptr;
    RectangleShape* m_pEndSquare = nullptr;

    Node* m_pStartNode = nullptr;
    Node* m_pEndNode = nullptr;

    std::vector<Node*> m_allCheckPoints;
    std::vector<std::vector<Node*>> m_allPath;

    PathFinder m_pathfinder;

    std::vector<Node*> m_pathToGoal;
};

