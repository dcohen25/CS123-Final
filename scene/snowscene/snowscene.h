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

    const static int screenWidth;
    const static int screenHeight;

protected:

    void loadPhongShader();
    void loadQuadShader();
    void loadShadowShader();
    void loadSkyboxShader();

    void setLights();
    void initLights();
    void updateSceneMap();
    void renderPhongScene(View *context);
    void renderPhongPass(View *context);
    void renderShadowPass(View *context);
    void renderSkyboxPass(View *context);
    void renderTexturePass(View *context);
    void renderQuadPass(View *context);
    void setPhongUniforms(View *context);
    bool createRenderTarget();
    void updateCurrentTile(View *context);
    void setQuadUniforms(View *context);
    void setShadowUniforms(View *context);
    void setSkyboxUniforms(View *context);
    void setTextureUniforms(View *context);
    bool isNewTile(glm::vec3 tile);
    void renderQuad();
    void addTile(glm::vec3 tile);
    void updateDepthMVP(View *context);
    void loadSkybox();
    void loadSkyboxVertices();
    void loadSkyboxVAO();
    GLuint loadCubemap(std::vector<const GLchar*> faces);
    void updateTilesToRender(View *context);
    void loadTexture();
    void renderShadowScene(View *context);

    CS123SceneLightData makeLight(int i);

    std::vector<CS123SceneLightData> m_lights;
    std::map<int, std::map<int, SnowSceneTile>> m_sceneMap;
    GLuint m_FramebufferName;
    GLuint m_depthTexture;
    GLuint m_skyboxTexture;
    GLuint m_barkTexture;
    GLuint m_skyboxVAO, m_skyboxVBO;
    GLuint m_cubemapTexture;
    glm::vec3 m_currentTile;
    glm::mat4 m_depthMVP;
    glm::mat4 m_depthBiasMVP;
    std::vector<SnowSceneTile> m_tilesToRender;


    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_quadShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_shadowShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_skyboxShader;

    SnowSceneTextures m_snowSceneTextures;
};

#endif // SCENEVIEWSCENE_H
