#ifndef ROOTSOLVER_H
#define ROOTSOLVER_H

#include <vector>
#include "glm.hpp"

class RootSolver
{
public:
    RootSolver();
    ~RootSolver();

    static std::vector<float> getQuadraticRoots(float A, float B, float C);
    static float getPlanarRoot(glm::vec4 p_eye, glm::vec4 d, glm::vec4 normal, glm::vec4 center);
    static float getDiscriminant(float A, float B, float C);
    static int getNumberOfRoots(float discriminant);
    static float getQuadraticRootOne(float A, float B, float C);
    static float getQuadraticRootTwo(float A, float B, float C);
    static float getSmallestRoot(std::vector<float> roots);
    static bool isValidRoot(float root);
};

#endif // ROOTSOLVER_H
