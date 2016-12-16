#ifndef CYLINDER_H
#define CYLINDER_H

#include "openglshape.h"
#include "circle.h"

class Cylinder : public OpenGLShape {

public:
    Cylinder(float diameter, float height, int xTess, int yTess, glm::mat4x4 transform);
    ~Cylinder();  // deconstruct a Cylinder

    void draw() override; // draw

private:
    float m_height; // height
    int m_xTess; // x tesselation
    int m_yTess; // y tesselation
    glm::mat4x4 m_transform; // transform
    float m_diameter; // diameter
    float m_theta; // theta
    std::unique_ptr<Circle> m_top;
    std::unique_ptr<Circle> m_bottom;
    glm::vec4 getNormal(float angle); // get normal at an angle
    void tesselate() override;  // tesselate a Cylinder
    void render() override; // render shape
    void renderTop(); // tesselate body
    void renderBottom(); // tesselate bottom cap
    glm::vec2 getTextureMap(glm::vec4 intersect);
};

#endif // CYLINDER_H
