#ifndef IMPLICITCIRCLE_H
#define IMPLICITCIRCLE_H

#include "implicitshape.h"

class ImplicitCircle : public ImplicitShape {
public:
    ImplicitCircle(glm::vec4 center, glm::vec4 normal);
    ~ImplicitCircle();

    float intersect(glm::vec4 p_eye, glm::vec4 d) override;
    glm::vec4 getNormal(glm::vec4 intersect) override;
    glm::vec2 getTextureMap(glm::vec4 intersect) override;
protected:
    bool isValidIntersection(glm::vec4 intersection);
    glm::vec4 m_normal;
    glm::vec4 m_center;
};

#endif // IMPLICITCIRCLE_H
