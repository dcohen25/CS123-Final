#ifndef SNOWSCENETILE_H
#define SNOWSCENETILE_H

#include <glm/glm.hpp>
#include "snowscenetile.h"
#include "lib/cs123scenedata.h"
#include "snowsceneobject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

class SnowSceneTile
{
public:
    SnowSceneTile(glm::vec3 coords);
    SnowSceneTile();
    ~SnowSceneTile();

    virtual void render(std::unique_ptr<CS123Shader> &shader,  std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);

    const static float tileSize;
    const static int numTrees;
    const static int numSnowmen;

protected:
    // initialize scene
    void initScene();

    void initTrees();
    void initSnowmen();
    void initSnow();

    glm::vec3 getRandomPositionOnTile();

    glm::vec3 m_coords;
    std::vector<SnowSceneObject> m_sceneObjects;
};

#endif // SNOWSCENETILE_H
