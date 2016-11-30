#ifndef CYLINDER_H
#define CYLINDER_H

#include "implicitshape.h"

class Cylinder : ImplicitShape
{
public:
    Cylinder();
    ~Cylinder();

    Intersect intersect(glm::vec4 p_eye, glm::vec4 d) override;
    glm::vec4 getNormal(glm::vec4 intersect) override;
};

#endif // CYLINDER_H
