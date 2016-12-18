#ifndef SNOWSCENETILE_H
#define SNOWSCENETILE_H

#include "snowsceneobject.h"
#include "view.h"

class SnowSceneTile
{
public:
    SnowSceneTile(glm::vec3 coords);
    SnowSceneTile();
    ~SnowSceneTile();

    void renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);

    const static float tileSize;
    const static int numTrees;
    const static int numSnowmen;
    const static int numOrnaments;

    BoundingBox getBoundingBox();

    void updateSceneObjects();

protected:
    // initialize scene
    void initScene();

    void initTrees();
    void initSnowmen();
    void initSnow();
    void initOrnaments();

    glm::vec3 getRandomPositionOnTile();

    glm::vec3 m_coords;
    std::vector<std::shared_ptr<SnowSceneObject>> m_sceneObjects;
    std::shared_ptr<SnowSceneObject> m_snow;
    BoundingBox m_boundingBox;
};

#endif // SNOWSCENETILE_H
