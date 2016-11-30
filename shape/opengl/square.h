#ifndef SQUARE_H
#define SQUARE_H

#include "openglshape.h"

class Square : public OpenGLShape  {

public:
    Square(float size, int xTess, glm::mat4x4 transform);
    ~Square();  // deconstruct a Square

private:
    int m_tess; // tesselation
    glm::mat4x4 m_transform; // transform
    float m_size; // square size;
    void tesselate() override;  // tesselate a Square

};

#endif // SQUARE_H
