#include "snowsceneobject.h"
#include "scene/utils.h"

const float SnowSceneObject::maxSpeed = .05f;

SnowSceneObject::SnowSceneObject(glm::vec3 coords, float length, float width, float height, float speed, glm::vec3 direction) :
    m_coords(coords),
    m_length(length),
    m_width(width),
    m_height(height),
    m_boundingBox(coords, length, width, height),
    m_speed(speed),
    m_direction(direction)
{
}

BoundingBox SnowSceneObject::getBoundingBox(){
    return m_boundingBox;
}

SnowSceneObject::~SnowSceneObject(){

}

glm::vec3 SnowSceneObject::getDirection(){
    return m_direction;
}

float SnowSceneObject::getLength(){
    return m_length;
}

float SnowSceneObject::getWidth(){
    return m_width;
}

float SnowSceneObject::getHeight(){
    return m_height;
}

void SnowSceneObject::setDirection(glm::vec3 direction){
    m_direction = direction;
}

void SnowSceneObject::setPosition(glm::vec3 position){
    m_coords = position;
    m_boundingBox = BoundingBox(m_coords, m_length, m_width, m_height);
    makeObject();
}

glm::vec3 SnowSceneObject::getNewPosition(){
    return m_coords + (m_speed * m_direction);
}

glm::vec3 SnowSceneObject::getRandomDirection(){
    glm::vec3 direction;
    direction.x = rand();
    direction.y = 0;
    direction.z = rand();
    return glm::normalize(direction);
}

float SnowSceneObject::getRandomSpeed(){
    return std::max(Utils::getRandomValue(), .5f) * SnowSceneObject::maxSpeed;
}

glm::vec3 SnowSceneObject::getCoords(){
    return m_coords;
}
