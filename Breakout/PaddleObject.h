#pragma once

#include "BallObject.h"
#include <SFML/Graphics.hpp>
#include <array>

class PaddleObject {
public:
    PaddleObject();
    void movePaddle(float move_x);
    void draw();
    
    const sf::Vector2f m_size;
    std::array<sf::Vector2f, 4> m_coordinates;
    std::array<BallObject, 2> m_endOfPaddle;
};