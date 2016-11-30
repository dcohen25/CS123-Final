#ifndef CONE_H
#define CONE_H

#include "openglshape.h"
#include "sphere.h"

class SnowMan : public OpenGLShape {

public:
    SnowMan(int xTess, int yTess, int radius, glm::mat4x4 transform);
    ~SnowMan();  // deconstruct a SnowMan

    void draw() override; // draw

private:
    int m_xTess; // x tesselation
    int m_yTess; // y tesselation
    int m_radius; // radius
    glm::mat4x4 m_transform; // transform
    void tesselate() override;  // tesselate a Cone
    std::unique_ptr<Sphere> m_bottom; // base of Snowman
    std::unique_ptr<Sphere> m_middle; // midsection of Snowman
    std::unique_ptr<Sphere> m_top; // top of Snowman
};

#endif // CONE_H
