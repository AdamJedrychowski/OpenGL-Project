#pragma once
#include "BallObject.h"
#include "BlockObject.h"
#include "PaddleObject.h"

#include <SFML/Graphics.hpp>
#include <list>

enum GameStatus {
    NO_ACTIVE = 0,
    ACTIVE = 1,
    PAUSED = 2
};

class Breakout {
public:
    Breakout();
    void runApp();

private:
    void createGameObjects();
    void LoadGameLevels();
    void checkWindowEdges();
    void detectCollision();
    void drawScene();
    void runGame();
    void updateBallPosition();
    void showMenuBar();
    
    GameStatus m_gameRunning;
    bool m_rightKeyPressed, m_leftKeyPressed;
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    int m_gameLevel = 0;
    std::string m_levels[3];
    std::list<std::pair<BlockObject, int>> m_blocks;
    BallObject m_ball;
    PaddleObject m_playerPaddle;
};