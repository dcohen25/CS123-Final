#ifndef SPHERE_H
#define SPHERE_H

#include "openglshape.h"
#include "circle.h"

class Sphere : public OpenGLShape {

public:
    Sphere(float radius, int xTess, int yTess, glm::mat4x4 transform);
    ~Sphere();  // deconstruct a sphere

private:
    int m_xTess; // x tesselation
    int m_yTess; // y tesselation
    glm::mat4x4 m_transform; // transform
    float m_radius; // sphere radius
    float m_theta; // sphere theta
    float m_phi; // sphere phi
    void tesselate() override;  // tesselate a sphere
    glm::vec4 getNormal(glm::vec4 vertex); // get normal at vertex

};

#endif // SPHERE_H
