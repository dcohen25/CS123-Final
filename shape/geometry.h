#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "glm/glm.hpp"

class Geometry
{
public:
    Geometry();
    ~Geometry();
    glm::vec4 normalize(glm::vec4 vertex);
};

#endif // GEOMETRY_H
