#include "PaddleObject.h"
#include <SFML/OpenGL.hpp>

PaddleObject::PaddleObject() :
    m_size(0.2f, 0.04f),
    m_coordinates{sf::Vector2f(-m_size.x / 2.0f, -1.0f + m_size.y),
                  sf::Vector2f(m_size.x / 2.0f, -1.0f + m_size.y),
                  sf::Vector2f(m_size.x / 2.0f, -1.0f),
                  sf::Vector2f(-m_size.x / 2.0f, -1.0f)},
    m_endOfPaddle{BallObject(sf::Vector2f(-m_size.x / 2.0f, -1.0f + m_size.y / 2), m_size.y / 2),
                  BallObject(sf::Vector2f(m_size.x / 2.0f, -1.0f + m_size.y / 2), m_size.y / 2)}
{
}

void PaddleObject::movePaddle(float move_x) {
    for(sf::Vector2f &it : m_coordinates) {
        it.x += move_x;
    }
    m_endOfPaddle[0].move(move_x);
    m_endOfPaddle[1].move(move_x);
}

void PaddleObject::draw() {
    m_endOfPaddle[0].draw();
    m_endOfPaddle[1].draw();

    glBegin(GL_QUADS);
    glColor3f(0.78f, 0.78f, 0.78f);
    for(sf::Vector2f &it : m_coordinates) {
        glVertex2f(it.x, it.y);
    }
    glEnd();
}