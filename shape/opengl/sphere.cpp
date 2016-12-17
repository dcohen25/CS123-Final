#include "sphere.h"

#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

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
                addVertices(m_transform * topVertex, m_transform * topNormal, getTextureMap(topVertex));
                addVertices(m_transform * leftVertex, m_transform * leftNormal, getTextureMap(leftVertex));
                addVertices(m_transform * rightVertex, m_transform * rightNormal, getTextureMap(rightVertex));
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
                addVertices(m_transform * topVertex, m_transform * topNormal, getTextureMap(topVertex));
                addVertices(m_transform * leftVertex, m_transform * leftNormal, getTextureMap(leftVertex));
                addVertices(m_transform * rightVertex, m_transform * rightNormal, getTextureMap(rightVertex));
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
                addVertices(m_transform * topVertex, m_transform * topNormal, getTextureMap(topVertex));
                addVertices(m_transform * leftVertex, m_transform * leftNormal, getTextureMap(leftVertex));
                addVertices(m_transform * rightVertex, m_transform * rightNormal, getTextureMap(rightVertex));
            }
        }
    }
}

glm::vec2 Sphere::getTextureMap(glm::vec4 intersect){
    glm::vec2 coords;
    float phi = asin(intersect.y / .5);
    coords.y = -(phi / M_PI) + .5;
    if (coords.y == 0 || coords.y == 1){
        coords.x = .5;
    }
    else {
        float angle = atan2(intersect.z, intersect.x);
        if (angle < 0 && angle > -.00001){
            coords.x = 1;
        }
        else if (angle <= 0){
            coords.x = -angle / (2.0 * M_PI);
        }
        else {
            coords.x = (angle / (2.0 * M_PI));
        }
    }
    return coords;
}

// get normal
glm::vec4 Sphere::getNormal(glm::vec4 vertex){
    glm::vec4 normal(vertex[0], vertex[1], vertex[2], 0.0);
    return glm::normalize(normal);
}
