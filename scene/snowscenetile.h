#ifndef SNOWSCENETILE_H
#define SNOWSCENETILE_H

#include <glm/glm.hpp>
#include "lib/cs123scenedata.h"

class SnowSceneTile
{
public:
    SnowSceneTile(float x, float y, int numTrees, int numSnowmen, float treeRadius, float snowmanRadius, float gridSize);
    SnowSceneTile();
    ~SnowSceneTile();

    std::vector<CS123ScenePrimitive> getPrimitives();
    std::vector<glm::mat4x4> getTransformations();

private:
    // initialize scene
    void initScene();
    void initPrimitives();
    void initTransformations();
    void initLights();
    void initGlobals();

    void initTreePrimitives();
    void initSnowmanPrimitives();
    void initSnowPrimitive();

    void initTreeTransformations();
    void initSnowmanTransformations();
    void initSnowTransformation();

    glm::mat4x4 computeTreeTransformation();
    std::vector<glm::mat4x4> computeSnowmanTransformation();
    glm::mat4x4 computeSnowmanTopTransformation();
    glm::mat4x4 computeSnowmanMiddleTransformation();
    glm::mat4x4 computeSnowmanBottomTransformation();
    glm::mat4x4 computeSnowTransformation();

    CS123ScenePrimitive makeTree();
    std::vector<CS123ScenePrimitive> makeSnowman();
    CS123ScenePrimitive makeSnowmanSphere();
    CS123ScenePrimitive makeSnow();
    CS123SceneLightData makeLight(int id);

    glm::vec2 m_coords;

    glm::vec3 getRandomObjectPosition();

    std::vector<CS123ScenePrimitive> m_primitives;
    std::vector<glm::mat4x4> m_transformations;

    int m_numTrees;
    int m_numSnowmen;
    float m_treeRadius;
    float m_snowmanRadius;
    float m_gridSize;
};

#endif // SNOWSCENETILE_H
