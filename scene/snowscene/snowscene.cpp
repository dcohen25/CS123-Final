#include "snowscene.h"

#include "GL/glew.h"
#include <QGLWidget>
#include "lib/resourceloader.h"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "gl/util/FullScreenQuad.h"
#include "soil/SOIL.h"
#include "view.h"
using namespace CS123::GL;

const int SnowScene::sceneRadius = 1;
const int SnowScene::numLights = 1;

SnowScene::SnowScene()
{
    loadSkybox();
    loadSkyboxShader();
    loadPhongShader();
    loadShadowShader();
    loadQuadShader();
    createRenderTarget();
    initLights();
}

SnowScene::~SnowScene()
{
}

void SnowScene::loadSkybox(){
    GLfloat skyboxVertices[] = {
           // Positions
           -1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

           -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
       };

       m_skyboxVAO, m_skyboxVBO;
       glGenVertexArrays(1, &m_skyboxVAO);
       glGenBuffers(1, &m_skyboxVBO);
       glBindVertexArray(m_skyboxVAO);
       glBindBuffer(GL_ARRAY_BUFFER, m_skyboxVBO);
       glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
       glEnableVertexAttribArray(0);
       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
       glBindVertexArray(0);

       // Cubemap (Skybox)
           std::vector<const GLchar*> faces;
           faces.push_back("skybox/test_left2.png");
           faces.push_back("skybox/test_right1.png");
           faces.push_back("skybox/test_top3.png");
           faces.push_back("skybox/test_bottom4.png");
           faces.push_back("skybox/test_back6.png");
           faces.push_back("skybox/test_front5.png");

            m_cubemapTexture = loadCubemap(faces);

}


void SnowScene::loadSkyboxShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/skybox.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/skybox.frag");
    m_skyboxShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
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
     glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1920, 1200, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
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
    glViewport(0,0,1920, 1200); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shadowShader->bind();
    setShadowUniforms(context);
    renderShadowScene(context);
    m_shadowShader->unbind();
}

void SnowScene::setShadowUniforms(View *context){
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    m_shadowShader->setUniform("depthMVP", m_depthMVP);
}

void SnowScene::renderPhongPass(View *context) {
    // Clear the screen
    // Render to our framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,1920, 1200); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    m_phongShader->bind();
    setPhongUniforms(context);
    setLights();
    renderPhongScene(context);
    m_phongShader->unbind();
}

void SnowScene::renderQuadPass(View *context) {
    // Clear the screen
    // Render to the screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,1920, 1200); // Render on the whole framebuffer, complete from the lower left corner to the upper right
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
    GLuint texID = glGetUniformLocation(SnowScene::m_quadShader->getID(), "renderedTexture");
    glUniform1i(texID, 0);
}

void SnowScene::render(View *context) {
    setClearColor();
    renderSkyboxPass(context);
    renderShadowPass(context);
    renderPhongPass(context);
}

void SnowScene::updateScene(View *context){
    updateCurrentTile(context);
    updateDepthMVP(context);
    updateSceneMap();
    updateTilesToRender(context);
}

void SnowScene::updateTilesToRender(View *context){
    m_tilesToRender.clear();
    for (int i = -SnowScene::sceneRadius; i <= SnowScene::sceneRadius; i++){
        for (int j = -SnowScene::sceneRadius; j <= SnowScene::sceneRadius; j++){
            int x = m_currentTile.x + (j * SnowSceneTile::tileSize);
            int z = m_currentTile.z + (i * SnowSceneTile::tileSize);
            if (context->getCamera()->isVisible(m_sceneMap[x][z].getBoundingBox())){
                m_tilesToRender.push_back(m_sceneMap[x][z]);
            }
        }
    }
}

void SnowScene::updateCurrentTile(View *context){
    m_currentTile.x = round(context->getCamera()->getEye().x / SnowSceneTile::tileSize) * SnowSceneTile::tileSize;
    m_currentTile.y = 0;
    m_currentTile.z = round(context->getCamera()->getEye().z / SnowSceneTile::tileSize) * SnowSceneTile::tileSize;
}

void SnowScene::updateDepthMVP(View *context){
    glm::mat4 biasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0
    );
    glm::vec3 currentPosition = glm::vec3(context->getCamera()->getEye());
    // Compute the MVP matrix from the light's point of view
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-SnowSceneTile::tileSize * SnowScene::sceneRadius * 2,
                                                        SnowSceneTile::tileSize * SnowScene::sceneRadius * 2,
                                                        -SnowSceneTile::tileSize * SnowScene::sceneRadius * 2,
                                                        SnowSceneTile::tileSize * SnowScene::sceneRadius * 2,
                                                        -SnowSceneTile::tileSize * SnowScene::sceneRadius * 2,
                                                        SnowSceneTile::tileSize * SnowScene::sceneRadius * 2 + 20);
    glm::mat4 depthViewMatrix = glm::lookAt(glm::vec3(currentPosition.x, currentPosition.y + 2, currentPosition.z - 6),
                                            currentPosition, glm::vec3(0,1,0));
    glm::mat4 depthModelMatrix = glm::mat4(1.0);
    glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;


    m_depthMVP = depthMVP;
    m_depthBiasMVP = biasMatrix * depthMVP;
}

void SnowScene::setPhongUniforms(View *context) {
    m_phongShader->setUniform("depthBiasMVP", m_depthBiasMVP);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    GLuint texID = glGetUniformLocation(m_phongShader->getID(), "shadowMap");
    glUniform1i(texID, 0);


    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", true);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
    m_phongShader->setUniform("allBlack", glm::vec3(1.0f, 1.0f, 1.0f));
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
    light.dir = glm::vec4(0, -2, 6, 0);
    light.color.r = light.color.g = light.color.b = 1;
    light.id = id;
    return light;
}

void SnowScene::addTile(glm::vec3 tile){
    m_sceneMap[tile.x][tile.z] = SnowSceneTile(tile);
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

void SnowScene::renderShadowScene(View *context){
   for (int i = 0; i < m_tilesToRender.size(); i++){
       m_tilesToRender[i].renderShadowScene(m_snowSceneTextures, m_shadowShader, context, m_shapes);
   }
}

void SnowScene::renderPhongScene(View *context){
   for (int i = 0; i < m_tilesToRender.size(); i++){
       m_tilesToRender[i].renderPhongScene(m_snowSceneTextures, m_phongShader, context, m_shapes);
   }
}


void SnowScene::renderSkyboxPass(View *context){
           // Clear buffers
         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


         // Draw skybox first
         glDepthMask(GL_FALSE);// Remember to turn depth writing off
         m_skyboxShader->bind();
         glm::mat4 view = glm::mat4(glm::mat3(context->getCamera()->getViewMatrix()));	// Remove any translation component of the view matrix
         glm::mat4 projection = context->getCamera()->getProjectionMatrix();
         m_skyboxShader->setUniform("view", view);
         m_skyboxShader->setUniform("projection", projection);
         // skybox cube
         glBindVertexArray(m_skyboxVAO);
         glActiveTexture(GL_TEXTURE0);
         glUniform1i(glGetUniformLocation(m_skyboxShader->getID(), "skybox"), 0);
         glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture);
         glDrawArrays(GL_TRIANGLES, 0, 36);
         glBindVertexArray(0);
         m_skyboxShader->unbind();
         glDepthMask(GL_TRUE);

}

GLuint SnowScene::loadCubemap(std::vector<const GLchar*> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width,height;
    unsigned char* image;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}
