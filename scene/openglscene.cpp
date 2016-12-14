#include "scene/openglscene.h"

#include <iostream>
#include "shape/opengl/cone.h"
#include "shape/opengl/cube.h"
#include "shape/opengl/sphere.h"
#include "shape/opengl/cylinder.h"
#include "shape/opengl/terrain.h"

OpenGLScene::OpenGLScene()
{
    initShapes();
}

OpenGLScene::~OpenGLScene(){

}

void OpenGLScene::setClearColor() {
    glClearColor(0, 0, 0, 0);
}

void OpenGLScene::initShapes(){
    m_shapes[PrimitiveType::PRIMITIVE_CUBE] = std::make_unique<Cube>(1, 10, glm::mat4x4());
    m_shapes[PrimitiveType::PRIMITIVE_CONE] = std::make_unique<Cone>(1, 1, 10, 10, glm::mat4x4());
    m_shapes[PrimitiveType::PRIMITIVE_SPHERE] = std::make_unique<Sphere>(.5f, 10, 10, glm::mat4x4());
    m_shapes[PrimitiveType::PRIMITIVE_CYLINDER] = std::make_unique<Cylinder>(1, 1, 10, 10, glm::mat4x4());
    m_shapes[PrimitiveType::PRIMITIVE_TERRAIN] = std::make_unique<Terrain>(10.5);
}
