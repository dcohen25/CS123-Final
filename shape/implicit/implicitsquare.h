#ifndef IMPLICITSQUARE_H
#define IMPLICITSQUARE_H

#include "glm.hpp"
#include "implicitshape.h"

class ImplicitSquare : public ImplicitShape
{
public:
    ImplicitSquare(glm::vec4 center, glm::vec4 normal);
    ~ImplicitSquare();

    float intersect(glm::vec4 p_eye, glm::vec4 d) override;
    glm::vec4 getNormal(glm::vec4 intersect) override;

private:
    glm::vec4 m_center;
    glm::vec4 m_normal;
    bool isValidIntersection(glm::vec4 intersection);

};

#endif // IMPLICITSQUARE_H
