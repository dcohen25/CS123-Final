#include "boundingbox.h"

#include <iostream>

BoundingBox::BoundingBox(glm::vec3 center, float length, float width, float height) :
    m_center(center),
    m_length(length),
    m_width(width),
    m_height(height),
    m_minX(m_center.x - width),
    m_maxX(m_center.x + width),
    m_minY(m_center.y - height),
    m_maxY(m_center.y + height),
    m_minZ(m_center.z - length),
    m_maxZ(m_center.z + length),
    m_topFaceBottomLeft(m_center.x - m_width / 2, m_center.y + m_height / 2, m_center.z + m_length / 2),
    m_topFaceBottomRight(m_center.x + m_width / 2, m_center.y + m_height / 2, m_center.z + m_length / 2),
    m_topFaceTopLeft(m_center.x - m_width / 2, m_center.y + m_height / 2, m_center.z - m_length / 2),
    m_topFaceTopRight(m_center.x + m_width / 2, m_center.y + m_height / 2, m_center.z - m_length / 2),
    m_bottomFaceBottomLeft(m_center.x - m_width / 2, m_center.y - m_height / 2, m_center.z + m_length / 2),
    m_bottomFaceBottomRight(m_center.x + m_width / 2, m_center.y - m_height / 2, m_center.z + m_length / 2),
    m_bottomFaceTopLeft(m_center.x - m_width / 2, m_center.y - m_height / 2, m_center.z - m_length / 2),
    m_bottomFaceTopRight(m_center.x + m_width / 2, m_center.y - m_height / 2, m_center.z - m_length / 2)
{
}

BoundingBox::BoundingBox(){

}

BoundingBox::~BoundingBox(){

}

float BoundingBox::getMinX(){
    return m_minX;
}

float BoundingBox::getMinY(){
    return m_minY;
}

float BoundingBox::getMinZ(){
    return m_minZ;
}

float BoundingBox::getMaxX(){
    return m_maxX;
}

float BoundingBox::getMaxY(){
    return m_maxY;
}

float BoundingBox::getMaxZ(){
    return m_maxZ;
}

glm::vec3 BoundingBox::getTopFaceBottomLeft(){
    return m_topFaceBottomLeft;
}

glm::vec3 BoundingBox::getTopFaceBottomRight(){
    return m_topFaceBottomRight;
}

glm::vec3 BoundingBox::getTopFaceTopLeft(){
    return m_topFaceTopLeft;
}

glm::vec3 BoundingBox::getTopFaceTopRight(){
    return m_topFaceTopRight;
}

glm::vec3 BoundingBox::getBottomFaceBottomLeft(){
    return m_bottomFaceBottomLeft;
}

glm::vec3 BoundingBox::getBottomFaceBottomRight(){
    return m_bottomFaceBottomRight;
}

glm::vec3 BoundingBox::getBottomFaceTopLeft(){
    return m_bottomFaceTopLeft;
}

glm::vec3 BoundingBox::getBottomFaceTopRight(){
    return m_bottomFaceTopRight;
}

bool BoundingBox::isIntersection(BoundingBox o){
    return (m_minX <= o.getMaxX() && m_maxX >= o.getMinX()) &&
         (m_minY <= o.getMaxY() && m_maxY >= o.getMinY()) &&
         (m_minZ <= o.getMaxZ() && m_maxZ >= o.getMinZ());
}
