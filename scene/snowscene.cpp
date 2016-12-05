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
using namespace CS123::GL;

SnowScene::SnowScene(float size, int radius, int numTrees, int numSnowmen, float treeRadius, float snowmanRadius, float maxTreeHeight, float maxSnowmanHeight) :
    OpenGLScene(SnowSceneTile(glm::vec3(0, 0, 0), size, numTrees, numSnowmen, treeRadius, snowmanRadius, maxTreeHeight, maxSnowmanHeight), radius),
    m_numTrees(numTrees),
    m_numSnowmen(numSnowmen),
    m_treeRadius(treeRadius),
    m_snowmanRadius(snowmanRadius),
    m_maxSnowmanHeight(maxSnowmanHeight),
    m_maxTreeHeight(maxTreeHeight)
{
    loadPhongShader();
    initLights();
}

SnowScene::~SnowScene()
{
}


OpenGLSceneTile SnowScene::makeSceneTile(glm::vec3 coords, float size){
    return SnowSceneTile(coords, size, m_numTrees, m_numSnowmen, m_treeRadius, m_snowmanRadius, m_maxTreeHeight, m_maxSnowmanHeight);
}

void SnowScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SnowScene::render(View *context) {
    updateCurrentTile(context->getCamera()->getEye());
    updateScene();
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_phongShader->bind();
    setSceneUniforms(context);
    setLights();
    renderScene(m_phongShader);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();
}


void SnowScene::setSceneUniforms(View *context) {
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

void SnowScene::initLights(){
    for (int i = 0; i < m_numLights; i++){
        CS123SceneLightData light = makeLight(i);
        m_lights.push_back(light);
    }
}

CS123SceneLightData SnowScene::makeLight(int id){
    CS123SceneLightData light;
    memset(&light, 0, sizeof(light));
    light.type = LightType::LIGHT_POINT;
    light.pos = glm::vec4(glm::vec3(0, 20, 0), 1.f);
    light.color.r = light.color.g = light.color.b = 1;
    light.id = id;
    return light;
}
