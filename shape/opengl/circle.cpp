#include "circle.h"

#include <glm/glm.hpp>
#include <iostream>

// construct a circle on XZ axis
Circle::Circle(float radius, int xTess, int yTess, glm::mat4x4 transform) :
    m_radius(radius),
    m_theta((2 * M_PI) / yTess),
    m_xTess(xTess),
    m_yTess(yTess),
    m_transform(transform)
{
    render();
}

// deconstruct a circle
Circle::~Circle() {

}

// tesselate Circle
void Circle::tesselate() {
    // iterate over x tesselation
    for (int i = 0; i < m_xTess; i++){
        // create inner circle radius
        float r1 = m_radius * (static_cast<float>(i) / m_xTess);
        float r2 = m_radius * (static_cast<float>(i + 1) / m_xTess);
        // iterate over y tesselation
        for (int j = 0; j < m_yTess; j++){
            // get tile verteces
            glm::vec4 topVertex(r1 * cos(j * m_theta), 0, r1 * sin(j * m_theta), 1.0);
            glm::vec4 leftVertex(r2 * cos((j + 1) * m_theta), 0, r2 * sin((j + 1) * m_theta), 1.0);
            glm::vec4 rightVertex(r2 * cos(j * m_theta), 0, r2 * sin(j * m_theta), 1.0);
            // get tile normals
            glm::vec4 normal(0.0, 1.0, 0.0, 0.0);
            // create tile of verteces and normals
            addVertices(m_transform * topVertex, m_transform * normal, m_transform * leftVertex, m_transform * normal, m_transform * rightVertex, m_transform * normal);
            // if outside center of circletopVertex
            if (i > 0){
                // get adjacent tile verteces
                topVertex = glm::vec4(r1 * cos(j * m_theta), 0, r1 * sin(j * m_theta), 1.0);
                leftVertex = glm::vec4(r1 * cos((j + 1)  * m_theta), 0, r1 * sin((j + 1)  * m_theta), 1.0);
                rightVertex = glm::vec4(r2 * cos((j + 1) * m_theta), 0, r2 * sin((j + 1) * m_theta), 1.0);
                // get adjacent tile normals
                addVertices(m_transform * topVertex, m_transform * normal, m_transform * leftVertex, m_transform * normal, m_transform * rightVertex, m_transform * normal);
            }
        }
    }
}
