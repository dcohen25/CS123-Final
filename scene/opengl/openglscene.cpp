#include "openglscene.h"

#include "shape/opengl/openglshape.h"
#include "shape/opengl/cube.h"
#include "shape/opengl/cone.h"
#include "shape/opengl/sphere.h"
#include "shape/opengl/cylinder.h"
OpenGLScene::OpenGLScene() :
    Scene()
{
    initShapes();
}

OpenGLScene::~OpenGLScene(){

}

void OpenGLScene::setClearColor() {
    glClearColor(0, 0, 0, 0);
}

void OpenGLScene::initShapes(){
    m_shapes[PrimitiveType::PRIMITIVE_CUBE] = std::make_unique<Cube>(1, 30, glm::mat4x4());
    m_shapes[PrimitiveType::PRIMITIVE_CONE] = std::make_unique<Cone>(1, 1, 30, 30, glm::mat4x4());
    m_shapes[PrimitiveType::PRIMITIVE_SPHERE] = std::make_unique<Sphere>(.5, 30, 30, glm::mat4x4());
    m_shapes[PrimitiveType::PRIMITIVE_CYLINDER] = std::make_unique<Cylinder>(1, 1, 30, 30, glm::mat4x4());
}
