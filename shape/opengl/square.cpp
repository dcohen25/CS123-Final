#include "square.h"

#include <glm/glm.hpp>
#include <iostream>

// construct a square
Square::Square(float size, int tess, glm::mat4x4 transform) :
    m_size(size),
    m_tess(tess),
    m_transform(transform)
{
    render();
}

// deconstruct a Square
Square::~Square() {

}

// tesselate Square
void Square::tesselate() {
    for (int i = 0; i < m_tess; i++){
        float z1  = -(m_size / 2.0) + (m_size * (static_cast<float>(i)  / m_tess));
        float z2 = -(m_size / 2.0) + (m_size * (static_cast<float>(i + 1)  / m_tess));
       // iterate over each square's verteces
        for (int j = 0; j < m_tess; j++){
            float x1 = -(m_size / 2) + (m_size * (static_cast<float>(j) / m_tess));
            float x2 = -(m_size / 2) + (m_size * (static_cast<float>(j + 1) / m_tess));

            // get tile verteces
            glm::vec4 topVertex(x1, 0, z1, 1.0);
            glm::vec4 leftVertex(x1, 0, z2, 1.0);
            glm::vec4 rightVertex(x2, 0, z1, 1.0);
            // get normal
            glm::vec4 normal(0.0, 1.0, 0.0, 0.0);
            // create tile of verteces and normals
            addVertices(m_transform * topVertex, m_transform * normal, getTextureMap(topVertex));
            addVertices(m_transform * leftVertex, m_transform * normal, getTextureMap(leftVertex));
            addVertices(m_transform * rightVertex, m_transform * normal, getTextureMap(rightVertex));
            // get adjacent tile verteces
            topVertex = glm::vec4(x2, 0, z1, 1.0);
            leftVertex = glm::vec4(x1, 0, z2, 1.0);
            rightVertex = glm::vec4(x2, 0, z2, 1.0);
            // create tile of verteces and normals
            addVertices(m_transform * topVertex, m_transform * normal, getTextureMap(topVertex));
            addVertices(m_transform * leftVertex, m_transform * normal, getTextureMap(leftVertex));
            addVertices(m_transform * rightVertex, m_transform * normal, getTextureMap(rightVertex));        }
    }
}

glm::vec2 Square::getTextureMap(glm::vec4 intersect){
    glm::vec2 uvCoords;
    uvCoords = glm::vec2(intersect.x + .5, intersect.z + .5);
    return uvCoords;
}
