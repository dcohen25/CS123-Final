#include "ornament.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "snowscenetile.h"
#include "scene/utils.h"

const float Ornament::bottomDiameter = .5f;
const float Ornament::topDiameter = .1f;

Ornament::Ornament(glm::vec3 coords) :
    SnowSceneObject(coords, Ornament::bottomDiameter , Ornament::bottomDiameter, Ornament::bottomDiameter + Ornament::topDiameter, 0, glm::vec3(0))
{
    initColors();
    setColor();
    makeObject();
}

Ornament::~Ornament(){

}

void Ornament::setColor(){
    int colorIdx = Utils::getRandomValue() * m_colors.size();
    m_color = m_colors[colorIdx];
}

void Ornament::renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) {
    renderShadowSceneTop(textures, shader, context, shapes);
    renderShadowSceneBottom(textures, shader, context, shapes);
}

void Ornament::renderShadowSceneTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) {
    shader->setUniform("m", m_ornamentTopTransformation);
    shapes[m_ornamentTopPrimitive.type]->draw();
}

void Ornament::renderShadowSceneBottom(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) {
    shader->setUniform("m", m_ornamentBottomTransformation);
    shapes[m_ornamentBottomPrimitive.type]->draw();
}

void Ornament::renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) {
   renderPhongSceneTop(textures, shader, context, shapes);
   renderPhongSceneBottom(textures, shader, context, shapes);
}

void Ornament::renderPhongSceneTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) {
    shader->setUniform("m", m_ornamentTopTransformation);
    shader->applyMaterial(m_ornamentTopPrimitive.material);
    shapes[m_ornamentTopPrimitive.type]->draw();
}

void Ornament::renderPhongSceneBottom(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) {
    shader->setUniform("m", m_ornamentBottomTransformation);
    shader->applyMaterial(m_ornamentBottomPrimitive.material);
    shapes[m_ornamentBottomPrimitive.type]->draw();
}

void Ornament::makeObject(){
    initOrnamentTop();
    initOrnamentBottom();
}

void Ornament::initOrnamentTop(){
    initOrnamentTopPrimitive();
    initOrnamentTopTransformation();
}

void Ornament::initOrnamentBottom(){
    initOrnamentBottomPrimitive();
    initOrnamentBottomTransformation();
}

void Ornament::initColors(){
    m_colors.push_back(glm::vec3(.3, 0, 0));
    m_colors.push_back(glm::vec3(0, .3, 0));
    m_colors.push_back(glm::vec3(0, 0, .3));
    m_colors.push_back(glm::vec3(.3, .3, .3));
}

void Ornament::initOrnamentTopPrimitive(){
    CS123ScenePrimitive ornament;
    ornament.type = PrimitiveType::PRIMITIVE_SPHERE;
    ornament.material.clear();
    glm::vec3 color = glm::vec3(.8, .3, 0);
    ornament.material.cAmbient = glm::vec4(color, 1);
    ornament.material.cDiffuse = glm::vec4(color, 1);
    ornament.material.cSpecular.r = ornament.material.cSpecular.g = ornament.material.cSpecular.b = 1;
    ornament.material.shininess = 100;

    m_ornamentTopPrimitive = ornament;
}


void Ornament::initOrnamentTopTransformation(){
    glm::mat4x4 ornamentTopTransformation;
    ornamentTopTransformation = glm::translate(ornamentTopTransformation, glm::vec3(m_coords.x, Ornament::bottomDiameter + Ornament::topDiameter / 2, m_coords.z));
    ornamentTopTransformation = glm::scale(ornamentTopTransformation, glm::vec3(Ornament::topDiameter, Ornament::topDiameter, Ornament::topDiameter));
    m_ornamentTopTransformation = ornamentTopTransformation;
}

void Ornament::initOrnamentBottomPrimitive(){
    CS123ScenePrimitive ornament;
    ornament.type = PrimitiveType::PRIMITIVE_SPHERE;
    ornament.material.clear();
    ornament.material.cAmbient = glm::vec4(m_color, 1);
    ornament.material.cDiffuse =  glm::vec4(m_color, 1);
    ornament.material.cSpecular.r = ornament.material.cSpecular.g = ornament.material.cSpecular.b = 1;
    ornament.material.shininess = 100;

    m_ornamentBottomPrimitive = ornament;
}

void Ornament::initOrnamentBottomTransformation(){
    glm::mat4x4 ornamentBottomTransformation;
    ornamentBottomTransformation = glm::translate(ornamentBottomTransformation, glm::vec3(m_coords.x, Ornament::bottomDiameter / 2, m_coords.z));
    ornamentBottomTransformation = glm::scale(ornamentBottomTransformation, glm::vec3(Ornament::bottomDiameter, Ornament::bottomDiameter, Ornament::bottomDiameter));

    m_ornamentBottomTransformation = ornamentBottomTransformation;
}
