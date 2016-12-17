#include "cylinder.h"

#include <glm/glm.hpp>
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include <iostream>

// construct a Cylinder on XZ axis
Cylinder::Cylinder(float diameter, float height, int xTess, int yTess, glm::mat4x4 transform) :
    m_diameter(diameter),
    m_theta((2 * M_PI) / yTess),
    m_top(nullptr),
    m_bottom(nullptr),
    m_height(height),
    m_xTess(xTess),
    m_yTess(yTess),
    m_transform(transform)
{
    render();
}

// deconstruct a Cylinder
Cylinder::~Cylinder() {

}


// draw
void Cylinder::draw(){
    m_top->draw();
    m_bottom->draw();

    OpenGLShape::draw();
}

// render
void Cylinder::render(){
    renderTop();
    renderBottom();

    OpenGLShape::render();
}

// tesselate top
void Cylinder::renderTop(){
    // translate to top of cylinder
    glm::mat4 transform = glm::translate(m_transform, glm::vec3(0, m_height / 2.0, 0));
    m_top = std::make_unique<Circle>(m_diameter / 2, m_xTess, m_yTess, transform);
}

// tesselate bottom
void Cylinder::renderBottom(){
    // translate bottom to base of cylinder
    glm::mat4 transform = glm::translate(m_transform, glm::vec3(0, -m_height / 2.0, 0));
    // rotate bottom
    transform = glm::rotate(transform, static_cast<float>(M_PI), glm::vec3(1, 0, 0));
    m_bottom = std::make_unique<Circle>(m_diameter / 2, m_xTess, m_yTess, transform);
}

// tesselate body
void Cylinder::tesselate(){
    for (int i = 0; i < m_xTess; i++){
        // circles
        float r = m_diameter / 2.0;
        float y1 = (m_height / 2.0) - (m_height * (static_cast<float>(i)  / m_xTess));
        float y2 = (m_height / 2.0) - (m_height * (static_cast<float>(i + 1)  / m_xTess));
       // iterate over each cirle's verteces
        for (int j = 0; j < m_yTess; j++){
            // get tile verteces
            glm::vec4 topVertex(r * cos(-j * m_theta), y1, r * sin(-j * m_theta), 1.0);
            glm::vec4 leftVertex(r * cos(-j * m_theta), y2, r * sin(-j * m_theta), 1.0);
            glm::vec4 rightVertex(r * cos(-(j + 1) * m_theta), y1, r * sin(-(j + 1) * m_theta), 1.0);
            // get adjacent tile normals
            glm::vec4 topNormal(getNormal(-j * m_theta));
            glm::vec4 leftNormal(getNormal(-j * m_theta));
            glm::vec4 rightNormal(getNormal(-(j + 1) * m_theta));
            // create tile of verteces and normals
            addVertices(m_transform * topVertex, m_transform * topNormal, getTextureMap(topVertex));
            addVertices(m_transform * leftVertex, m_transform * leftNormal, getTextureMap(leftVertex));
            addVertices(m_transform * rightVertex, m_transform * rightNormal, getTextureMap(rightVertex));
            // get adjacent tile verteces
            topVertex = glm::vec4(r * cos(-(j + 1) * m_theta), y1, r * sin(-(j + 1) * m_theta), 1.0);
            leftVertex = glm::vec4(r * cos(-j * m_theta), y2, r * sin(-j * m_theta), 1.0);
            rightVertex = glm::vec4(r * cos(-(j + 1) * m_theta), y2, r * sin(-(j + 1) * m_theta), 1.0);
            // get adjacent tile normals
            topNormal = glm::vec4(getNormal(-(j + 1) * m_theta));
            leftNormal = glm::vec4(getNormal(-j * m_theta));
            rightNormal = glm::vec4(getNormal(-(j + 1) * m_theta));
            // create tile of verteces and normals
            addVertices(m_transform * topVertex, m_transform * topNormal, getTextureMap(topVertex));
            addVertices(m_transform * leftVertex, m_transform * leftNormal, getTextureMap(leftVertex));
            addVertices(m_transform * rightVertex, m_transform * rightNormal, getTextureMap(rightVertex));
        }
    }
}

glm::vec2 Cylinder::getTextureMap(glm::vec4 intersect){
    glm::vec2 coords;
    coords.y = -intersect.y + .5;
    float angle = atan2(intersect.z, intersect.x);
    if (angle < 0 && angle > -.00001){
        coords.x = 1;
    }
    else if (angle <= 0){
        coords.x = -angle / (2.0 * M_PI);
    }
    else {
        coords.x = 1 - (angle / (2.0 * M_PI));
    }
    return coords;
}

glm::vec4 Cylinder::getNormal(float angle){
    glm::vec4 normal(cos(angle), 0.0, sin(angle), 0.0);
    return glm::normalize(normal);
}
