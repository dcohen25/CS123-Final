#ifndef IMPLICITSPHERE_H
#define IMPLICITSPHERE_H

#include "glm.hpp"
#include "implicitshape.h"
#include <vector>

class ImplicitSphere : public ImplicitShape
{
public:
    ImplicitSphere();
    ~ImplicitSphere();

    glm::vec4 getNormal(glm::vec4 intersect) override;
    float intersect(glm::vec4 p_eye, glm::vec4 d) override;
    glm::vec2 getTextureMap(glm::vec4 intersect) override;

private:
    std::vector<float> filterValidRoots(glm::vec4 p_eye, glm::vec4 d, std::vector<float> roots);
};

#endif // IMPLICITSPHERE_H
