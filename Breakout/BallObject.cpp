#include "BallObject.h"
#include <SFML/OpenGL.hpp>

BallObject::BallObject(sf::Vector2f position, float radious) :
    m_position(position), m_radious(radious)
{
}

void BallObject::moveByVelocity(float dt) {
    m_position += m_velocity * dt;
}

void BallObject::move(float dx, float dy) {
    m_position.x += dx;
    m_position.y += dy;
}

void BallObject::draw() {
    glBegin( GL_TRIANGLE_FAN );
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(m_position.x, m_position.y);
    float t = 2 * 3.14159274101257324219f / 100.0f;
    for( int n = 0; n <= 100; ++n ) {
        glVertex2f(m_position.x + sin(t * n) * m_radious, m_position.y + cos(t * n) * m_radious);
    }
    glEnd();
}

void BallObject::setVelocity(sf::Vector2f velocity) {
    m_velocity = velocity;
}
