#ifndef TERRAIN_H
#define TERRAIN_H

#include "openglshape.h"

class Terrain : public OpenGLShape
{
public:
    Terrain(float width);
//    Terrain();
    Terrain& operator=(const Terrain&) = delete;
    Terrain(const Terrain& terrain);
    ~Terrain();

private:
    float randValue(int row, int col);
    glm::vec3 getPosition(int row, int col);
    glm::vec3 getNormal(int row, int col);
    void tesselate() override;

    int m_numRows, m_numCols;
    float m_width;
};

#endif // TERRAIN_H
