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
