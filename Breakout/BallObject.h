#pragma once

#include <SFML/Graphics.hpp>

class BallObject {
public:
    BallObject(sf::Vector2f position, float radious);
    void moveByVelocity(float dt);
    void move(float dx = 0, float dy = 0);
    void draw();
    void setVelocity(sf::Vector2f velocity);

    sf::Vector2f m_position;
    float m_radious;
    sf::Vector2f m_velocity;
};