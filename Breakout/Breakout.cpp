#include "Breakout.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>
#include "imgui.h" 
#include "imgui-SFML.h"

#include <iostream>
#include <algorithm>
#include <numbers>

Breakout::Breakout() :
    m_gameRunning(NO_ACTIVE),
    m_rightKeyPressed(false),
    m_leftKeyPressed(false),
    m_window(sf::VideoMode(1280, 960), "Breakout"),
    m_ball(sf::Vector2f(0.0f, -0.92f), 0.03f)
{
    ImGui::SFML::Init(m_window);
    m_window.setVerticalSyncEnabled(true);
    glViewport(0, 0, (GLsizei)m_window.getSize().x, (GLsizei)m_window.getSize().y);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    LoadGameLevels();
    createGameObjects();
}

void Breakout::createGameObjects() {
    BlockObject::size = sf::Vector2f(2.0f / 15, 1.0f / 8);

    m_blocks.clear();
    int lv;
    for(int i=0; i<8; ++i) {
        for(int j=0; j<15; ++j) {
            lv = m_levels[m_gameLevel][i * 15 + j] - '0';
            if(lv != 0) {
                m_blocks.push_back(std::pair(BlockObject(j, 7 - i), lv));
            }
        }
    }
}

void Breakout::LoadGameLevels(){
    m_levels[0] = std::string("111111111111111") +
                              "111111111111111" +
                              "111111111111111" +
                              "111111111111111" +
                              "111111111111111" +
                              "111111111111111" +
                              "000000000000000" +
                              "000000000000000";

    m_levels[1] = std::string("000000222000000") +
                              "011111111111110" +
                              "012121212121210" +
                              "011212121212110" +
                              "011111333111110" +
                              "011112111211110" +
                              "000011101110000" +
                              "000000000000000";

    m_levels[2] = std::string("011111111111110") +
                              "111111111111111" +
                              "112121444121211" +
                              "114212121212411" +
                              "114141333141411" +
                              "113112111211311" +
                              "000011101110000" +
                              "000300000003000";
}

void Breakout::checkWindowEdges() {
    if(m_ball.m_position.x - m_ball.m_radious <= -1.0f)
    {
        m_ball.m_velocity.x *= -1;
        m_ball.m_position.x -= 2 * (m_ball.m_position.x - m_ball.m_radious + 1.0f);
    }
    else if (m_ball.m_position.x + m_ball.m_radious >= 1.0f)
    {
        m_ball.m_velocity.x *= -1;
        m_ball.m_position.x -= 2 * (m_ball.m_position.x + m_ball.m_radious - 1.0f);
    }
    if (m_ball.m_position.y + m_ball.m_radious >= 1.0f)
    {
        m_ball.m_velocity.y *= -1;
        m_ball.m_position.y -= 2 * (m_ball.m_position.y + m_ball.m_radious - 1);
    }
}

void Breakout::detectCollision() {
    sf::Vector2f nearest_point = sf::Vector2f(), distance_vec = sf::Vector2f();
    float distance, overlap;
    nearest_point.x = std::clamp(m_ball.m_position.x, m_playerPaddle.m_coordinates[0].x, m_playerPaddle.m_coordinates[2].x);
    nearest_point.y = std::clamp(m_ball.m_position.y, m_playerPaddle.m_coordinates[2].y, m_playerPaddle.m_coordinates[0].y);

    distance_vec = nearest_point - m_ball.m_position;
    distance = sqrt(distance_vec.x*distance_vec.x + distance_vec.y*distance_vec.y);
    overlap = m_ball.m_radious - distance;
    
    if(std::isnan(overlap)) overlap = 0;
    if(overlap > 0) {
        distance_vec /= distance;
        m_ball.m_position -= distance_vec * overlap;

        if(distance_vec.x == 0.0f) {
            m_ball.m_velocity.y *= -1;
        } else if(distance_vec.y == 0.0f) {
            m_ball.m_velocity.x *= -1;
        } else if(distance_vec == sf::Vector2f(0.0f, 0.0f)) {
            m_ball.m_velocity.x *= -1;
            m_ball.m_velocity.y *= -1;
        }
        return;
    }


    for(auto block = m_blocks.begin(); block != m_blocks.end(); ++block) {
        nearest_point.x = std::clamp(m_ball.m_position.x, block->first.m_coordinates[0].x, block->first.m_coordinates[2].x);
        nearest_point.y = std::clamp(m_ball.m_position.y, block->first.m_coordinates[0].y, block->first.m_coordinates[2].y);

        distance_vec = nearest_point - m_ball.m_position;
        distance = sqrt(distance_vec.x*distance_vec.x + distance_vec.y*distance_vec.y);
        overlap = m_ball.m_radious - distance;
        
        if(std::isnan(overlap)) overlap = 0;
        if(overlap > 0) {
            distance_vec /= distance;
            m_ball.m_position -= distance_vec * overlap;
            if(distance_vec.x == 0.0f) {
                m_ball.m_velocity.y *= -1;
            } else if(distance_vec.y == 0.0f) {
                m_ball.m_velocity.x *= -1;
            } else if(distance_vec == sf::Vector2f(0.0f, 0.0f)) {
                m_ball.m_velocity.x *= -1;
                m_ball.m_velocity.y *= -1;
            }
            if(--block->second == 0) m_blocks.erase(block);
            break;
        }
    }
}

void Breakout::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for(auto &block : m_blocks) {
        block.first.draw(block.second);
    }
    m_playerPaddle.draw();
    m_ball.draw();
}

void Breakout::runGame() {
    if(m_gameRunning == NO_ACTIVE) {
        srand(time(NULL));
        m_ball.setVelocity(sf::Vector2f((float)rand() / (float)RAND_MAX - 0.5f, 0.7f));
    }
    m_gameRunning = ACTIVE;
    m_deltaClock.restart();
}

void Breakout::updateBallPosition() {
    float time = m_deltaClock.restart().asSeconds();
    if(m_gameRunning == PAUSED) return;

    m_ball.moveByVelocity(time);
    checkWindowEdges();
    if(m_leftKeyPressed && m_playerPaddle.m_coordinates[0].x > m_playerPaddle.m_endOfPaddle[0].m_radious / 2 - 1.0f)
        m_playerPaddle.movePaddle(-0.7f * time);
    if(m_rightKeyPressed && m_playerPaddle.m_coordinates[1].x < 1.0f - m_playerPaddle.m_endOfPaddle[0].m_radious / 2)
        m_playerPaddle.movePaddle(0.7f * time);

    detectCollision();
}

void Breakout::showMenuBar() {
    ImGui::Begin("Menu");
    ImGui::SetWindowSize(ImVec2(160, 100));
    std::string text_option;
    if(m_gameRunning == ACTIVE) text_option = "Stop";
    else if(m_gameRunning == NO_ACTIVE) {
        text_option = "Start";
        if(ImGui::InputInt("Level", &m_gameLevel)) {
            if(m_gameLevel < 0) m_gameLevel = 0;
            else if(m_gameLevel > 2) m_gameLevel = 2;
            createGameObjects();
        }
    }
    else text_option = "Resume";
    if(ImGui::Button(text_option.c_str(), ImVec2(100,40))) { runGame(); }
    ImGui::End();
}

void reshapeScreen(sf::Vector2u size)
{
    glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Breakout::runApp() {
    m_window.setFramerateLimit(60);
    bool windowOpen = true;
    sf::Event event;

    while (windowOpen)
    {
        while (m_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) windowOpen = false;
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) m_gameRunning = PAUSED;
            if(m_gameRunning == ACTIVE) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) m_rightKeyPressed = true;
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) m_leftKeyPressed = true;
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) m_rightKeyPressed = false;
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) m_leftKeyPressed = false;
                if (event.type == sf::Event::Resized) reshapeScreen(m_window.getSize());
            }
        }

        if(m_gameRunning == ACTIVE) {
            updateBallPosition();
            drawScene();
        } else {
            drawScene();
            ImGui::SFML::Update(m_window, m_deltaClock.restart());
            showMenuBar();
            ImGui::SFML::Render(m_window);
        }
        m_window.display();
    }
    ImGui::SFML::Shutdown();
}