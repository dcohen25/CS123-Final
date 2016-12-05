#include "openglsceneobject.h"

OpenGLSceneObject::std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> OpenGLSceneObject::m_shapes = init_map();

OpenGLSceneObject::OpenGLSceneObject()
{

}

OpenGLSceneObject::~OpenGLSceneObject(){

}

void OpenGLSceneObject::transform(glm::mat4x4 transformation){
    for (int i = 0; i < m_transformations.size(); i++){
        m_transformations[i] = transformation * m_transformations[i];
    }
}

void OpenGLSceneObject::render(std::unique_ptr<CS123Shader> &shader){
    for (int i = 0; i < m_primitives.size(); i++){
        shader->setUniform("m", m_transformations[i]);
        shader->applyMaterial(m_primitives[i].material);
        m_shapes[m_primitives[i].type]-draw();
    }
}
