#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape {

public:
    Triangle(glm::vec3 top, glm::vec3 left, glm::vec3 right, float length, float width, float height, glm::vec3 center, int xTess, int yTess);
    ~Triangle();  // deconstruct a Triangle

    void tesselate() override;  // tesselate a Triangle

#endif // TRIANGLE_H
