#include "snowscene.h"

#include "GL/glew.h"
#include <QGLWidget>
#include "camera/camera.h"
#include "ui/view.h"
#include "lib/resourceloader.h"
#include "glm.hpp"
#include "lib/cs123scenedata.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "gl/shaders/CS123Shader.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"
#include "gl/util/FullScreenQuad.h"

using namespace CS123::GL;

const int SnowScene::sceneRadius = 1;
const int SnowScene::numLights = 3;

SnowScene::SnowScene() :
    m_currentTile(0, 0, 0)
{
    loadPhongShader();
    loadQuadShader();
    loadShadowShader();
    createRenderTarget();
    initLights();
}

SnowScene::~SnowScene()
{
}

void SnowScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SnowScene::loadQuadShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/quad.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/quad.frag");
    m_quadShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SnowScene::loadShadowShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/shadow.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/shadow.frag");
    m_shadowShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

bool SnowScene::createRenderTarget(){
    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
     m_FramebufferName = 0;
     glGenFramebuffers(1, &m_FramebufferName);
     glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferName);

     // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
     glGenTextures(1, &m_depthTexture);
     glBindTexture(GL_TEXTURE_2D, m_depthTexture);
     glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1500, 1500, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

     glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthTexture, 0);

     glDrawBuffer(GL_NONE); // No color buffer is drawn to.

     // Always check that our framebuffer is ok
     if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
         return false;
     }
     return true;
}

void SnowScene::renderShadowPass(View *context){
    // Clear the screen
    // Render to our framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferName);
    glViewport(0,0,1500,1500); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shadowShader->bind();
    setShadowUniforms(context);
    renderScene(m_shadowShader);
    m_shadowShader->unbind();
}

void SnowScene::setShadowUniforms(View *context){
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    m_shadowShader->setUniform("depthMVP", m_depthMVP[m_currentTile.x][m_currentTile.z]);
}
void SnowScene::renderPhongPass(View *context) {
    // Clear the screen
    // Render to our framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,1500,1500); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_phongShader->bind();
    setPhongUniforms(context);
    setLights();
    renderScene(m_phongShader);
    m_phongShader->unbind();
}

void SnowScene::renderQuadPass(View *context) {
    // Clear the screen
    // Render to the screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,1500,1500); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_quadShader->bind();
    setQuadUniforms(context);
    renderQuad();
    m_quadShader->unbind();
}

void SnowScene::renderQuad(){
    std::unique_ptr<FullScreenQuad> quad = std::make_unique<FullScreenQuad>();
    quad->draw();
}

void SnowScene::setQuadUniforms(View *context){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    // Set our "renderedTexture" sampler to user Texture Unit 0
    GLuint texID = glGetUniformLocation(m_quadShader->getID(), "renderedTexture");
    glUniform1i(texID, 0);
}

void SnowScene::render(View *context) {
    setClearColor();
    renderShadowPass(context);
    renderPhongPass(context);
}

void SnowScene::updateScene(View *context){
    updateCurrentTile(context->getCamera()->getEye());
    updateSceneMap();
}

void SnowScene::addTile(glm::vec3 tile){
    addTileToMap(tile);
    addLightInvDir(tile);
    addDepthMVP(tile);
    addDepthBiasMVP(tile);
}

void SnowScene::addLightInvDir(glm::vec3 tile){
    glm::vec3 lightInvDir = createLightInvDir(tile);
    m_lightInvDir[tile.x][tile.z] = lightInvDir;
}

glm::vec3 SnowScene::createLightInvDir(glm::vec3 tile){
    return glm::vec3(tile.x + 2, tile.y + 2, tile.z + 2);
}

void SnowScene::addTileToMap(glm::vec3 tile){
    m_sceneMap[tile.x][tile.z] = std::make_unique<SnowSceneTile>(tile);
}

void SnowScene::addDepthMVP(glm::vec3 tile){
    glm::mat4 depthMVP = createDepthMVP(tile);
    m_depthMVP[tile.x][tile.z] = depthMVP;
}

void SnowScene::addDepthBiasMVP(glm::vec3 tile){
    glm::mat4 depthBiasMVP = createDepthBiasMVP(tile);
    m_depthBiasMVP[tile.x][tile.z] = depthBiasMVP;
}

glm::mat4 SnowScene::createDepthMVP(glm::vec3 tile){
    // Compute the MVP matrix from the light's point of view
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-SnowScene::sceneRadius * 2 * SnowSceneTile::tileSize,
                                                        SnowScene::sceneRadius * 2 * SnowSceneTile::tileSize,
                                                        -SnowSceneTile::tileSize * 2 * SnowScene::sceneRadius,
                                                        SnowSceneTile::tileSize * 2 * SnowScene::sceneRadius,
                                                        -SnowSceneTile::tileSize * SnowScene::sceneRadius * 2,
                                                        SnowSceneTile::tileSize * SnowScene::sceneRadius * 2 + 20);
    glm::mat4 depthViewMatrix = glm::lookAt(m_lightInvDir[tile.x][tile.z], tile, glm::vec3(0,1,0));
    glm::mat4 depthModelMatrix = glm::mat4(1.0);
    glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
    return depthMVP;
}

glm::mat4 SnowScene::createDepthBiasMVP(glm::vec3 tile){
    glm::mat4 biasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0
    );
    return biasMatrix * m_depthMVP[tile.x][tile.z];
}


void SnowScene::setPhongUniforms(View *context) {
    m_phongShader->setUniform("depthBiasMVP", m_depthBiasMVP[m_currentTile.x][m_currentTile.z]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    GLuint texID = glGetUniformLocation(m_phongShader->getID(), "shadowMap");
    glUniform1i(texID, 1);


    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", true);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
//    m_phongShader->setUniform("allBlack", glm::vec3(1.0f, 1.0f, 1.0f));
}

void SnowScene::setLights()
{
    // TODO: [SCENEVIEW] Fill this in...
    //
    // Set up the lighting for your scene using m_phongShader.
    // The lighting information will most likely be stored in CS123SceneLightData structures.
    //
    for (int i = 0; i < m_lights.size(); i++){
        m_phongShader->setLight(m_lights[i]);
    }
}

bool SnowScene::isNewTile(glm::vec3 tile){
    return m_sceneMap.count(tile.x) == 0 || m_sceneMap[tile.x].count(tile.z) == 0;
}

void SnowScene::initLights(){
    for (int i = 0; i < SnowScene::numLights; i++){
        CS123SceneLightData light = makeLight(i);
        m_lights.push_back(light);
    }
}

CS123SceneLightData SnowScene::makeLight(int id){
    CS123SceneLightData light;
    memset(&light, 0, sizeof(light));
    light.type = LightType::LIGHT_DIRECTIONAL;
    light.dir = glm::vec4(-2, -2, -2, 0);
    light.color.r = light.color.g = light.color.b = 1;
    light.id = id;
    return light;
}

void SnowScene::updateSceneMap(){
    for (int i = -SnowScene::sceneRadius; i <= SnowScene::sceneRadius; i++){
        for (int j = -SnowScene::sceneRadius; j <= SnowScene::sceneRadius; j++){
            int x = m_currentTile.x + (j * SnowSceneTile::tileSize);
            int z = m_currentTile.z + (i * SnowSceneTile::tileSize);
            glm::vec3 tile = glm::vec3(x, 0, z);
            if (isNewTile(tile)){
                addTile(tile);
            }
        }
    }
}

void SnowScene::renderScene(std::unique_ptr<CS123::GL::CS123Shader> &shader){
    for (int i = -SnowScene::sceneRadius; i <= SnowScene::sceneRadius; i++){
        for (int j = -SnowScene::sceneRadius; j <= SnowScene::sceneRadius; j++){
            int x = m_currentTile.x + (j * SnowSceneTile::tileSize);
            int z = m_currentTile.z + (i * SnowSceneTile::tileSize);
            m_sceneMap[x][z]->render(shader, m_shapes);
        }
    }
}

void SnowScene::updateCurrentTile(glm::vec4 eye){
    if (eye.x > m_currentTile.x + SnowSceneTile::tileSize / 2){
        m_currentTile.x += SnowSceneTile::tileSize;
    }
    else if (eye.x < m_currentTile.x - SnowSceneTile::tileSize / 2){
        m_currentTile.x -= SnowSceneTile::tileSize;
    }
    else if (eye.z > m_currentTile.z + SnowSceneTile::tileSize / 2){
        m_currentTile.z += SnowSceneTile::tileSize;
    }
    else if (eye.z < m_currentTile.z - SnowSceneTile::tileSize/ 2){
        m_currentTile.z -= SnowSceneTile::tileSize;
    }
}
