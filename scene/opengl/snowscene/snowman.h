#ifndef SNOWMAN_H
#define SNOWMAN_H

#include "lib/cs123scenedata.h"

class Snowman
{
public:
    Snowman();
    ~Snowman();
private:
    std::vector<CS123ScenePrimitive> m_primitives;
    std::vector<glm::mat4x4> m_transformations;
};

#endif // SNOWMAN_H
