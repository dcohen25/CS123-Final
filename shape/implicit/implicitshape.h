#ifndef IMPLICITSHAPE_H
#define IMPLICITSHAPE_H

#include "glm.hpp"

class ImplicitShape
{
public:
    ImplicitShape();
    ~ImplicitShape();

    virtual float intersect(glm::vec4 p_eye, glm::vec4 d);
    virtual glm::vec4 getNormal(glm::vec4 intersect);
    virtual glm::vec2 getTextureMap(glm::vec4 intersect);
};
#endif // IMPLICITSHAPE_H
