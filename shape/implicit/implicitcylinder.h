#ifndef IMPLICITCYLINDER_H
#define IMPLICITCYLINDER_H

#include "glm.hpp"
#include "implicitcircle.h"
#include <vector>

class ImplicitCylinder : public ImplicitShape
{
public:
    ImplicitCylinder();
    ~ImplicitCylinder();

    glm::vec4 getNormal(glm::vec4 intersect) override;
    float intersect(glm::vec4 p_eye, glm::vec4 d) override;
    glm::vec2 getTextureMap(glm::vec4 intersect) override;
private:
    std::vector<float> filterValidRoots(glm::vec4 p_eye, glm::vec4 d, std::vector<float> roots);
    std::vector<float> intersectBody(glm::vec4 p_eye, glm::vec4 d);
    float intersectTop(glm::vec4 p_eye, glm::vec4 d);
    float intersectBottom(glm::vec4 p_eye, glm::vec4 d);
    ImplicitCircle m_top;
    ImplicitCircle m_bottom;
};

#endif // IMPLICITCYLINDER_H
