#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "glm.hpp"

class BoundingBox
{
public:
    BoundingBox(glm::vec3 center, float length, float width, float height);
    BoundingBox();
    ~BoundingBox();

    glm::vec3 getTopFaceBottomLeft();
    glm::vec3 getTopFaceBottomRight();
    glm::vec3 getTopFaceTopLeft();
    glm::vec3 getTopFaceTopRight();
    glm::vec3 getBottomFaceBottomLeft();
    glm::vec3 getBottomFaceBottomRight();
    glm::vec3 getBottomFaceTopLeft();
    glm::vec3 getBottomFaceTopRight();

    bool isIntersection(BoundingBox o);

private:
    glm::vec3 m_center;
    float m_length;
    float m_width;
    float m_height;

    glm::vec3 m_topFaceBottomLeft;
    glm::vec3 m_topFaceBottomRight;
    glm::vec3 m_topFaceTopLeft;
    glm::vec3 m_topFaceTopRight;
    glm::vec3 m_bottomFaceBottomLeft;
    glm::vec3 m_bottomFaceBottomRight;
    glm::vec3 m_bottomFaceTopLeft;
    glm::vec3 m_bottomFaceTopRight;
};

#endif // BOUNDINGBOX_H
