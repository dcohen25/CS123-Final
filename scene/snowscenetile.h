#ifndef SNOWSCENETILE_H
#define SNOWSCENETILE_H

#include <glm/glm.hpp>
#include "openglscenetile.h"
#include "lib/cs123scenedata.h"
#include "openglsceneobject.h"

class SnowSceneTile : public OpenGLSceneTile
{
public:
    SnowSceneTile(glm::vec3 coords, float size, int numTrees, int numSnowmen, float treeRadius, float snowmanRadius, float maxSnowmanHeight, float maxTreeHeight);
    SnowSceneTile();
    ~SnowSceneTile();

protected:
    // initialize scene
    void initScene();

    void initTrees();
    void initSnowmen();
    void initSnow();

    void setRandomPositionOnTile(OpenGLSceneObject &object);

    int m_numTrees;
    int m_numSnowmen;
    float m_treeRadius;
    float m_snowmanRadius;
    float m_maxSnowmanHeight;
    float m_maxTreeHeight;
};

#endif // SNOWSCENETILE_H
