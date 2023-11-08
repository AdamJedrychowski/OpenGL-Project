#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class BlockObject {
public:
    BlockObject(int i, int j);
    void draw(int durability);

    std::array<sf::Vector2f, 4> m_coordinates;
    static sf::Vector2f size;
};