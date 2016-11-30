#ifndef CONE_H
#define CONE_H

#include "implicitcircle.h"
#include <vector>
#include "implicitshape.h"

class ImplicitCone : public ImplicitShape
{
public:
    ImplicitCone();
    ~ImplicitCone();

    float intersect(glm::vec4 p_eye, glm::vec4 d) override;
    glm::vec4 getNormal(glm::vec4 intersect) override;
    glm::vec2 getTextureMap(glm::vec4 intersect) override;
protected:
    std::vector<float> intersectBody(glm::vec4 p_eye, glm::vec4 d);
    float intersectBase(glm::vec4 p_eye, glm::vec4 d);
    std::vector<float> filterValidRoots(glm::vec4 p_eye, glm::vec4 d, std::vector<float> roots);
    bool isValidIntersection(glm::vec4 intersection);
    ImplicitCircle m_base;
};

#endif // CONE_H
