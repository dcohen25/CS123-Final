#include "tile.h"

#include <glm/glm.hpp>

// construct a Tile
Tile::Tile(glm::vec4 topVertex, glm::vec4 topNormal, glm::vec4 leftVertex, glm::vec4 leftNormal, glm::vec4 rightVertex, glm::vec4 rightNormal) :
    m_topVertex(topVertex),
    m_topNormal(topNormal),
    m_leftVertex(leftVertex),
    m_leftNormal(leftNormal),
    m_rightVertex(rightVertex),
    m_rightNormal(rightNormal)
{
}

// deconstruct a Tile
Tile::~Tile()
{
}
