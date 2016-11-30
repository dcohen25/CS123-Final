#ifndef CUBE_H
#define CUBE_H

#include "square.h"
#include "openglshape.h"

class Cube : public OpenGLShape {

public:
    Cube(float size, int xTess, glm::mat4x4 transform);
    ~Cube();  // deconstruct a cube

    void draw() override; // draw

private:
    int m_tess; // tesselation
    glm::mat4x4 m_transform; // transform
    float m_size; // cube size
    std::unique_ptr<Square> m_top;
    std::unique_ptr<Square> m_bottom;
    std::unique_ptr<Square> m_left;
    std::unique_ptr<Square> m_right;
    std::unique_ptr<Square> m_back;
    std::unique_ptr<Square> m_front;
    void tesselate() override;  // tesselate a cube
    void render() override; // render shape
    void renderFront(); // tesselate front
    void renderBack(); // tesselate back
    void renderTop(); // tesselate top
    void renderBottom(); // tesselate bottom
    void renderLeft(); // tesselate left
    void renderRight(); // tesselate right

};

#endif // CUBE_H
