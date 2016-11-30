#include "shape/geometry.h"

Geometry::Geometry()
{

}

Geometry::~Geometry()
{

}

glm::vec4 Geometry::normalize(glm::vec4 vertex){
    float length = sqrt(pow(vertex[0], 2.0) + pow(vertex[1], 2.0) + pow(vertex[2], 2.0));
    return glm::vec4(vertex[0] / length, vertex[1] / length, vertex[2] / length, 0);
}

