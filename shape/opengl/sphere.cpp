#include "sphere.h"

#include <glm/glm.hpp>

// construct a sphere
Sphere::Sphere(float radius, int xTess, int yTess, glm::mat4x4 transform) :
    m_radius(radius),
    m_theta(M_PI / xTess),
    m_phi((2 * M_PI) / yTess),
    m_xTess(xTess),
    m_yTess(yTess),
    m_transform(transform)
{
    render();
}

// deconstruct a sphere
Sphere::~Sphere()
{
}

// tesselate Sphere
void Sphere::tesselate() {
    // tesselate
    for (int i = 0; i < m_xTess; i++){
        // circle 1
        float r1 = m_radius * cos(((i * m_theta) + M_PI / 2));
        float y1 = m_radius * sin(((i * m_theta) + M_PI / 2));
        // circle 2
        float r2 = m_radius * cos((((i + 1) * m_theta) + M_PI / 2));
        float y2 = m_radius * sin((((i + 1) * m_theta) + M_PI / 2));
        // iterate over each cirle's verteces
        for (int j = 0; j < m_yTess; j++){
            if (i < m_xTess - 1){
                // get tile verteces
                glm::vec4 topVertex(r1 * cos(-j * m_phi), y1, r1 * sin(-j * m_phi), 1.0);
                glm::vec4 leftVertex(r2 * cos(-j * m_phi), y2, r2 * sin(-j * m_phi), 1.0);
                glm::vec4 rightVertex(r2 * cos(-(j + 1) * m_phi), y2, r2 * sin(-(j + 1) * m_phi), 1.0);
                // get adjacent tile normals
                glm::vec4 topNormal(getNormal(topVertex));
                glm::vec4 leftNormal(getNormal(leftVertex));
                glm::vec4 rightNormal(getNormal(rightVertex));
                // create tile of verteces and normals
                addVertices(m_transform * topVertex, m_transform * topNormal, m_transform * leftVertex, m_transform * leftNormal, m_transform * rightVertex, m_transform * rightNormal);
            }
            if (i > 0 && i < m_xTess - 1){
                // get adjacent tile verteces
                glm::vec4 topVertex(r1 * cos(-j * m_phi), y1, r1 * sin(-j * m_phi), 1.0);
                glm::vec4 leftVertex(r2 * cos(-(j + 1) * m_phi), y2, r2 * sin(-(j + 1) * m_phi), 1.0);
                glm::vec4 rightVertex(r1 * cos(-(j + 1) * m_phi), y1, r1 * sin(-(j + 1) * m_phi), 1.0);
                // get adjacent tile normals
                glm::vec4 topNormal(getNormal(topVertex));
                glm::vec4 leftNormal(getNormal(leftVertex));
                glm::vec4 rightNormal(getNormal(rightVertex));
                // create tile of verteces and normals
                addVertices(m_transform * topVertex, m_transform * topNormal, m_transform * leftVertex, m_transform * leftNormal, m_transform * rightVertex, m_transform * rightNormal);
            }
            else if (i == m_xTess - 1){
                // get bottom tile verteces
                glm::vec4 topVertex(r1 * cos(j * m_phi), y1, r1 * sin(j * m_phi), 1.0);
                glm::vec4 leftVertex(r1 * cos((j + 1) * m_phi), y1, r1 * sin((j + 1) * m_phi), 1.0);
                glm::vec4 rightVertex(r2 * cos(j * m_phi), y2, r2 * sin(j * m_phi), 1.0);
                // get bottom tile normals
                glm::vec4 topNormal(getNormal(topVertex));
                glm::vec4 leftNormal(getNormal(leftVertex));
                glm::vec4 rightNormal(getNormal(rightVertex));
                // create tile of verteces and normals
                addVertices(m_transform * topVertex, m_transform * topNormal, m_transform * leftVertex, m_transform * leftNormal, m_transform * rightVertex, m_transform * rightNormal);
            }
        }
    }
}

// get normal
glm::vec4 Sphere::getNormal(glm::vec4 vertex){
    glm::vec4 normal(vertex[0], vertex[1], vertex[2], 0.0);
    return glm::normalize(normal);
}
