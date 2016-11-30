#ifndef TILE_H
#define TILE_H

#include "glm.hpp"

struct Tile {
    Tile(glm::vec4 topVertex, glm::vec4 topNormal, glm::vec4 leftVertex, glm::vec4 leftNormal, glm::vec4 rightVertex, glm::vec4 rightNormal);
    ~Tile();
    // top vertex and normal
    glm::vec4 m_topVertex;
    glm::vec4 m_topNormal;
    // left vertex and normal
    glm::vec4 m_leftVertex;
    glm::vec4 m_leftNormal;
    // right vertex and normal;
    glm::vec4 m_rightVertex;
    glm::vec4 m_rightNormal;
};

#endif // TILE_H
