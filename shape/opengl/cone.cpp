#include "cone.h"

#include <glm/glm.hpp>
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include <iostream>

// construct a Cone
Cone::Cone(float diameter, float height, int xTess, int yTess, glm::mat4x4 transform) :
    m_diameter(diameter),
    m_theta((M_PI * 2) / yTess),
    m_base(nullptr),
    m_height(height),
    m_xTess(xTess),
    m_yTess(yTess),
    m_transform(transform)
{
    render();
}

// deconstruct a Cone
Cone::~Cone() {

}

// draw shape
void Cone::draw(){
    m_base->draw();
    OpenGLShape::draw();
}

void Cone::render() {
    renderBase();
    OpenGLShape::render();
}

void Cone::renderBase(){
    // render base
    glm::mat4 transform = glm::rotate(m_transform, static_cast<float>(M_PI), glm::vec3(1, 0, 0));
    transform = glm::translate(transform, glm::vec3(0, m_height / 2.0, 0));
    m_base = std::make_unique<Circle>(m_diameter / 2, m_xTess, m_yTess, transform);
}

void Cone::tesselate(){
    // tesselate body
    for (int i = 0; i < m_xTess; i++){
        // circle 1
        float r1 = (m_diameter / 2.0) * (static_cast<float>(i) / m_xTess);
        float y1 = ((m_height / 2.0)) - (m_height * (static_cast<float>(i)  / m_xTess));
        // circle 2
        float r2 = (m_diameter / 2.0) * (static_cast<float>(i + 1) / m_xTess);
        float y2 = ((m_height / 2.0)) - (m_height * (static_cast<float>(i + 1)  / m_xTess));
        // iterate over each cirle's verteces
        for (int j = 0; j < m_yTess; j++){
            if (i == 0){
                // get tile verteces
                glm::vec4 topVertex(r1 * cos(-j * m_theta), y1, r1 * sin(-j * m_theta), 1.0);
                glm::vec4 leftVertex(r2 * cos(-j * m_theta), y2, r2 * sin(-j * m_theta), 1.0);
                glm::vec4 rightVertex(r2 * cos(-(j + 1) * m_theta), y2, r2 * sin(-(j + 1) * m_theta), 1.0);
                // get adjacent tile normals
                glm::vec4 topNormal(getNormal(-j * m_theta));
                glm::vec4 leftNormal(getNormal(-j * m_theta));
                glm::vec4 rightNormal(getNormal(-(j + 1) * m_theta));
                // create tile of verteces and normals
                addVertices(m_transform * topVertex, m_transform * topNormal, m_transform * leftVertex, m_transform * leftNormal, m_transform * rightVertex, m_transform * rightNormal);
            }
            else if (i > 0){
                // get tile verteces
                glm::vec4 topVertex(r1 * cos(-j * m_theta), y1, r1 * sin(-j * m_theta), 1.0);
                glm::vec4 leftVertex(r2 * cos(-j * m_theta), y2, r2 * sin(-j * m_theta), 1.0);
                glm::vec4 rightVertex(r1 * cos(-(j + 1) * m_theta), y1, r1 * sin(-(j + 1) * m_theta), 1.0);
                // get tile normals
                glm::vec4 topNormal(getNormal(-j * m_theta));
                glm::vec4 leftNormal(getNormal(-j * m_theta));
                glm::vec4 rightNormal(getNormal(-(j + 1) * m_theta));
                // create tile of verteces and normals;
                addVertices(m_transform * topVertex, m_transform * topNormal, m_transform * leftVertex, m_transform * leftNormal, m_transform * rightVertex, m_transform * rightNormal);

                // get adjacent tile verteces
                topVertex = glm::vec4(r1 * cos(-(j + 1) * m_theta), y1, r1 * sin(-(j + 1) * m_theta), 1.0);
                leftVertex = glm::vec4(r2 * cos(-j * m_theta), y2, r2 * sin(-j * m_theta), 1.0);
                rightVertex = glm::vec4(r2 * cos(-(j + 1) * m_theta), y2, r2 * sin(-(j + 1) * m_theta), 1.0);
                // get adjacent tile normals
                topNormal = glm::vec4(getNormal(-(j + 1) * m_theta));
                leftNormal = glm::vec4(getNormal(-j * m_theta));
                rightNormal = glm::vec4(getNormal(-(j + 1) * m_theta));
                // create tile of verteces and normals;
                addVertices(m_transform * topVertex, m_transform * topNormal, m_transform * leftVertex, m_transform * leftNormal, m_transform * rightVertex, m_transform * rightNormal);
            }
        }
    }
}

// get normal
glm::vec4 Cone::getNormal(float angle){
    // get slope of cone
    float x1 = m_diameter / 2.0;
    float y1 = -(m_height / 2.0);
    float x2 = 0;
    float y2 = (m_height / 2.0);
    float slope = (y2 - y1) / (x2 - x1);
    // get normal x and y magnitudes
    float y = 1.0 / sqrt((slope * slope) + 1);
    // get normal vector
    glm::vec4 normal(cos(angle), y, sin(angle), 0.0);
    return glm::normalize(normal);
}
