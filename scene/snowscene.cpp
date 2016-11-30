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

SnowScene::SnowScene() :
    OpenGLScene(),
    m_currentTile(0, 0, 0)
{
    loadPhongShader();
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

void SnowScene::render(View *context) {
    updateCurrentTile(context->getCamera()->getEye());
    updateScene();
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_phongShader->bind();
    setSceneUniforms(context);
    setLights();
    renderScene();
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();
}

void SnowScene::updateScene(){
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            int x = m_currentTile.x + (j * m_gridSize);
            int z = m_currentTile.z + (i * m_gridSize);
            if (m_sceneMap.count(z) == 0 || m_sceneMap[z].count(x) == 0){
                m_sceneMap[z][x] = SnowSceneTile(x, z, m_numTrees, m_numSnowmen, m_treeRadius, m_snowmanRadius, m_gridSize);
            }
        }
    }
}

void SnowScene::renderScene(){
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            int x = m_currentTile.x + (j * m_gridSize);
            int z = m_currentTile.z + (i * m_gridSize);
            renderSceneTile(m_sceneMap[z][x]);
        }
    }
}

void SnowScene::updateCurrentTile(glm::vec4 eye){
    if (eye.x > m_currentTile.x + m_gridSize / 2){
        m_currentTile.x += m_gridSize;
    }
    else if (eye.x < m_currentTile.x - m_gridSize / 2){
        m_currentTile.x -= m_gridSize;
    }
    else if (eye.z > m_currentTile.z + m_gridSize / 2){
        m_currentTile.z += m_gridSize;
    }
    else if (eye.z < m_currentTile.z - m_gridSize / 2){
        m_currentTile.z -= m_gridSize;
    }
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

void SnowScene::renderSceneTile(SnowSceneTile tile) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // TODO: [SCENEVIEW] Fill this in...
    // You shouldn't need to write *any* OpenGL in this class!
    //
    //
    // This is where you should render the geometry of the scene. Use what you
    // know about OpenGL and leverage your Shapes classes to get the job done.
    //
    for (int i = 0; i < tile.getPrimitives().size(); i++){
        m_phongShader->setUniform("m", tile.getTransformations()[i]);
        m_phongShader->applyMaterial(tile.getPrimitives()[i].material);
        m_shapes[tile.getPrimitives()[i].type]->draw();
    }
}
