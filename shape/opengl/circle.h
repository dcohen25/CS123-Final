#ifndef CIRCLE_H
#define CIRCLE_H

#include "openglshape.h"

class Circle : public OpenGLShape {

public:
    Circle(float radius, int xTess, int yTess, glm::mat4x4 transform);
    ~Circle();  // deconstruct a Circle

private:
    int m_xTess; // x tesselation
    int m_yTess; // y tesselation
    glm::mat4x4 m_transform; // transform
    float m_radius; // radius of Circle
    float m_theta; // theta of Circle
    void tesselate() override;  // tesselate a Circle
    glm::vec2 getTextureMap(glm::vec4 intersect); // get texture map at intersection

};

#endif // CIRCLE_H
