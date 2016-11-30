#ifndef PLANARSHAPE_H
#define PLANARSHAPE_H

#include "glm.hpp"
#include "implicitshape.h"
class PlanarShape : public ImplicitShape
{
public:
    PlanarShape(glm::vec4 center, glm::vec4 normal);
    ~PlanarShape();

    float getRoot(glm::vec4 p_eye, glm::vec4 d);
protected:
    glm::vec4 m_center;
    glm::vec4 m_normal;
};

#endif // PLANARSHAPE_H
