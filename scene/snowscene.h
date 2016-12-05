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
    SnowScene(float size, int radius, int numTrees, int numSnowmen, float treeRadius, float snowmenRadius, float maxTreeHeight, float maxSnowmenHeight);
    virtual ~SnowScene();

    virtual void render(View *context) override;
    virtual OpenGLSceneTile makeSceneTile(glm::vec3 coords, float size) override;
    // Use this method to set an internal selection, based on the (x, y) position of the mouse
    // pointer.  This will be used during the "modeler" lab, so don't worry about it for now.
    void setSelection(int x, int y);

protected:

    void loadPhongShader();
    void setSceneUniforms(View *context);
    void setLights();
    void initLights();

    CS123SceneLightData makeLight(int i);

    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::vector<CS123SceneLightData> m_lights;
    int m_numLights;

    int m_numTrees;
    int m_numSnowmen;
    float m_treeRadius;
    float m_snowmanRadius;
    float m_maxSnowmanHeight;
    float m_maxTreeHeight;
};

#endif // SCENEVIEWSCENE_H
