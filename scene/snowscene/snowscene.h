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
    virtual void updateScene(View *context) override;
    // Use this method to set an internal selection, based on the (x, y) position of the mouse
    // pointer.  This will be used during the "modeler" lab, so don't worry about it for now.
    void setSelection(int x, int y);

    const static int sceneRadius;
    const static int numLights;

protected:

    void loadPhongShader();
    void loadQuadShader();
    void loadShadowShader();
    void setLights();
    void initLights();
    void updateSceneMap();
    void renderScene(std::unique_ptr<CS123::GL::CS123Shader> &shader);
    void renderPhongPass(View *context);
    void renderShadowPass(View *context);
    void renderQuadPass(View *context);
    void setPhongUniforms(View *context);
    bool createRenderTarget();
    void updateCurrentTile(glm::vec4 eye);
    void setQuadUniforms(View *context);
    void setShadowUniforms(View *context);
    bool isNewTile(glm::vec3 tile);
    void addDepthMVP(glm::vec3 tile);
    void addDepthBiasMVP(glm::vec3 tile);
    void addLightInvDir(glm::vec3 tile);
    glm::mat4 createDepthMVP(glm::vec3 tile);
    glm::mat4 createDepthBiasMVP(glm::vec3 tile);
    glm::vec3 createLightInvDir(glm::vec3 tile);
    void addTile(glm::vec3 tile);
    void addTileToMap(glm::vec3 tile);
    void renderQuad();

    CS123SceneLightData makeLight(int i);

    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_quadShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_shadowShader;
    std::vector<CS123SceneLightData> m_lights;
    std::map<int, std::map<int, glm::mat4>> m_depthMVP;
    std::map<int, std::map<int, glm::mat4>> m_depthBiasMVP;
    std::map<int, std::map<int, glm::vec3>> m_lightInvDir;
    std::map<int, std::map<int, std::unique_ptr<SnowSceneTile>>> m_sceneMap;
    glm::vec3 m_currentTile;
    GLuint m_FramebufferName;
    GLuint m_depthTexture;
};

#endif // SCENEVIEWSCENE_H
