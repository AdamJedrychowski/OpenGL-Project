#include "BlockObject.h"
#include <SFML/OpenGL.hpp>

sf::Vector2f BlockObject::size(0,0);

BlockObject::BlockObject(int i, int j) : 
    m_coordinates{sf::Vector2f(i * size.x - 0.99625f, j * size.y + 0.00375f),
                  sf::Vector2f(i * size.x - 0.99625f, (j + 1) * size.y - 0.00375f),
                  sf::Vector2f((i + 1) * size.x - 1.00375f, (j + 1) * size.y - 0.00375f),
                  sf::Vector2f((i + 1) * size.x - 1.00375f, j * size.y + 0.00375f)}
{
}

void BlockObject::draw(int durability) {
    glBegin(GL_QUADS);
    switch (durability)
    {
    case 1:
        glColor3f(0.0f, 0.8f, 0.0f);
        break;
    case 2:
        glColor3f(1.0f, 1.0f, 0.0f);
        break;
    case 3:
        glColor3f(1.0f, 0.6274f, 0.0f);
        break;
    case 4:
        glColor3f(1.0f, 0.0f, 0.0f);
        break;
    default:
        break;
    }
    for(sf::Vector2f &it : m_coordinates) {
        glVertex2f(it.x, it.y);
    }
    glEnd();
}