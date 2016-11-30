#include "cube.h"

#include <glm/glm.hpp>
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate

// construct a Cube on XZ axis
Cube::Cube(float size, int tess, glm::mat4x4 transform) :
    m_size(size),
    m_front(nullptr),
    m_back(nullptr),
    m_left(nullptr),
    m_right(nullptr),
    m_top(nullptr),
    m_bottom(nullptr),
    m_tess(tess),
    m_transform(transform)
{
    render();
}

// deconstruct a Cube
Cube::~Cube() {

}

// draw
void Cube::draw() {
    m_front->draw();
    m_back->draw();
    m_left->draw();
    m_right->draw();
    m_top->draw();
    m_bottom->draw();

    OpenGLShape::draw();
}

void Cube::tesselate(){}

void Cube::render(){
    renderFront();
    renderBack();
    renderTop();
    renderBottom();
    renderLeft();
    renderRight();

    OpenGLShape::render();
}

// tesselate Front
void Cube::renderFront(){
    // translate to front
    glm::mat4 transform = glm::translate(m_transform, glm::vec3(0, 0, m_size / 2.0));
    // rotate front
    transform = glm::rotate(transform, static_cast<float>(M_PI / 2), glm::vec3(1, 0, 0));
    m_front = std::make_unique<Square>(m_size, m_tess, transform);
}

// tesselate Back
void Cube::renderBack(){
    // translate to back
    glm::mat4 transform = glm::translate(m_transform, glm::vec3(0, 0, -m_size / 2.0));
    // rotate back
    transform = glm::rotate(transform, static_cast<float>(-M_PI / 2), glm::vec3(1, 0, 0));
    m_back= std::make_unique<Square>(m_size, m_tess, transform);
}

// tesselate Left
void Cube::renderLeft(){
    // translate to left
    glm::mat4 transform = glm::translate(m_transform, glm::vec3(-m_size / 2.0, 0, 0));
    // rotate left
    transform = glm::rotate(transform, static_cast<float>(M_PI / 2), glm::vec3(0, 0, 1));
    m_left = std::make_unique<Square>(m_size, m_tess, transform);
}

// tesselate Right
void Cube::renderRight(){
    // translate to Right
    glm::mat4 transform = glm::translate(m_transform, glm::vec3(m_size / 2.0, 0, 0));
    // rotate Right
    transform = glm::rotate(transform, static_cast<float>(-M_PI / 2), glm::vec3(0, 0, 1));
    m_right = std::make_unique<Square>(m_size, m_tess, transform);
}

// tesselate Top
void Cube::renderTop(){
    // translate to Top
    glm::mat4 transform = glm::translate(m_transform, glm::vec3(0, m_size / 2.0, 0));
    m_top = std::make_unique<Square>(m_size, m_tess, transform);
}

// tesselate Bottom
void Cube::renderBottom(){
    // translate to Bottom
    glm::mat4 transform = glm::translate(m_transform, glm::vec3(0, -m_size / 2.0, 0));
    // rotate bototm
    transform = glm::rotate(transform, static_cast<float>(M_PI), glm::vec3(1, 0, 0));
    m_bottom = std::make_unique<Square>(m_size, m_tess, transform);
}



