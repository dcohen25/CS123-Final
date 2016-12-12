#include "snowsceneobject.h"

SnowSceneObject::SnowSceneObject(glm::vec3 coords, float length, float width, float height) :
    m_coords(coords),
    m_length(length),
    m_width(width),
    m_height(height),
    m_boundingBox(coords, length, width, height)
{
}

BoundingBox SnowSceneObject::getBoundingBox(){
    return m_boundingBox;
}

SnowSceneObject::~SnowSceneObject(){

}

glm::vec3 SnowSceneObject::getCoords(){
    return m_coords;
}

void SnowSceneObject::render(std::unique_ptr<CS123Shader> &shader, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    for (int i = 0; i < m_primitives.size(); i++){
        shader->setUniform("m", m_transformations[i]);
        shader->applyMaterial(m_primitives[i].material);
        shapes[m_primitives[i].type]->draw();
    }
}
