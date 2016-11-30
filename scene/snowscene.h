#ifndef SNOWSCENE_H
#define SNOWSCENE_H

#include "scene/openglscene.h"

#include <memory>
#include <map>
#include "snowscenetile.h"
#include "camera/camera.h"

namespace CS123 { namespace GL {

    class CS123Shader;
    class Texture2D;
}}

/**
 *
 * @class SceneviewScene
 *
 * A complex scene consisting of multiple objects. Students will implement this class in the
 * Sceneview assignment.
 *
 * Here you will implement your scene graph. The structure is up to you - feel free to create new
 * classes and data structures as you see fit. We are providing this SceneviewScene class for you
 * to use as a stencil if you like.
 *
 * Keep in mind that you'll also be rendering entire scenes in the next two assignments, Intersect
 * and Ray. The difference between this assignment and those that follow is here, we are using
 * OpenGL to do the rendering. In Intersect and Ray, you will be responsible for that.
 */
class SnowScene : public OpenGLScene {
public:
    SnowScene();
    virtual ~SnowScene();

    virtual void render(View *context) override;

    // Use this method to set an internal selection, based on the (x, y) position of the mouse
    // pointer.  This will be used during the "modeler" lab, so don't worry about it for now.
    void setSelection(int x, int y);

private:

    void loadPhongShader();
    void setSceneUniforms(View *context);
    void setLights();
    void updateCurrentTile(glm::vec4 eye);
    void updateScene();
    void renderScene();
    void renderSceneTile(SnowSceneTile tile);
    void initLights();
    CS123SceneLightData makeLight(int i);

    std::map<int, std::map<int, SnowSceneTile>> m_sceneMap;
    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    int m_numTrees = 10;
    int m_numSnowmen = 3;
    int m_numLights = 10;
    float m_treeRadius = 9.f;
    float m_snowmanRadius = .3f;
    float m_gridSize = 15.f;
    glm::vec3 m_currentTile;
};

#endif // SCENEVIEWSCENE_H
