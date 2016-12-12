#include "boundingbox.h"

BoundingBox::BoundingBox(glm::vec3 center, float length, float width, float height) :
    m_center(center),
    m_length(length),
    m_width(width),
    m_height(height),
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
    return (m_topFaceTopRight.x > o.getTopFaceTopLeft().x && m_topFaceTopLeft.x < o.getTopFaceTopRight().x) &&
            (m_topFaceTopRight.y > o.getBottomFaceTopRight().y && m_bottomFaceTopRight.y < o.getTopFaceTopRight().y) &&
            (m_topFaceTopRight.z > o.getTopFaceBottomRight().z && m_topFaceBottomRight.z < o.getTopFaceTopRight().z);
}
