#include "snowman.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <iostream>

const float Snowman::maxDiameter = .6f;
const float Snowman::m_diameterBottomProportion = 1;
const float Snowman::m_diameterMiddleProportion = .8f;
const float Snowman::m_diameterTopProportion = .6f;
const float Snowman::m_diameterHatBaseProportion = .4f;
const float Snowman::m_diameterHatTopProportion = .2f;
const float Snowman::m_diameterNoseProportion = .1f;
const float Snowman::m_heightHatBaseProportion = .01f;
const float Snowman::m_heightHatTopProportion = .4f;
const float Snowman::m_heightNoseProportion = .4f;

//Texture2D Snowman::m_snowmanTopTexture = Snowman::loadTopTexture();

Snowman::Snowman(glm::vec3 coords, float diameter) :
    SnowSceneObject(coords, diameter, diameter, computeSnowmanHeight(diameter)),
    m_diameterBottom(diameter * Snowman::m_diameterBottomProportion),
    m_diameterMiddle(diameter * Snowman::m_diameterMiddleProportion),
    m_diameterTop(diameter * Snowman::m_diameterTopProportion),
    m_diameterHatBase(diameter * Snowman::m_diameterHatBaseProportion),
    m_diameterHatTop(diameter * Snowman::m_diameterHatTopProportion),
    m_diameterNose(diameter * Snowman::m_diameterNoseProportion),
    m_heightHatBase(diameter * Snowman::m_heightHatBaseProportion),
    m_heightHatTop(diameter * Snowman::m_heightHatTopProportion),
    m_heightNose(diameter * Snowman::m_heightNoseProportion)
{
    initSnowman();
}

Snowman::~Snowman(){

}

float Snowman::computeSnowmanHeight(float diameter){
    return diameter * Snowman::m_diameterBottomProportion +
    diameter * Snowman::m_diameterTopProportion +
    diameter * Snowman::m_diameterMiddleProportion +
    diameter * Snowman::m_heightHatBaseProportion +
    diameter * Snowman::m_heightHatTopProportion;
}

void Snowman::renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) {
    renderShadowTop(textures, shader, context, shapes);
    renderShadowMiddle(textures, shader, context, shapes);
    renderShadowBottom(textures, shader, context, shapes);
    renderShadowNose(textures, shader, context, shapes);
    renderShadowHat(textures, shader, context, shapes);
}

void Snowman::renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) {
    renderPhongTop(textures, shader, context, shapes);
    renderPhongMiddle(textures, shader, context, shapes);
    renderPhongBottom(textures, shader, context, shapes);
    renderPhongNose(textures, shader, context, shapes);
    renderPhongHat(textures, shader, context, shapes);
}

void Snowman::renderPhongTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    // TODO (Task 6): Initialize texture map.
    shader->setUniform("m", m_topTransformation);
    shader->setUniform("useTexture", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures.getSnowmanTopTexture());
    // Set our "renderedTexture" sampler to user Texture Unit 0
    GLuint texID = glGetUniformLocation(shader->getID(), "tex");
    glUniform1i(texID, 1);
    shapes[m_topPrimitive.type]->draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    shader->setUniform("useTexture", 0);
}

void Snowman::renderPhongMiddle(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_middleTransformation);
    shader->applyMaterial(m_middlePrimitive.material);
    shapes[m_middlePrimitive.type]->draw();
}

void Snowman::renderPhongBottom(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_bottomTransformation);
    shader->applyMaterial(m_bottomPrimitive.material);
    shapes[m_bottomPrimitive.type]->draw();
}

void Snowman::renderPhongNose(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_noseTransformation);
    shader->applyMaterial(m_nosePrimitive.material);
    shapes[m_nosePrimitive.type]->draw();
}

void Snowman::renderPhongHat(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    renderPhongHatTop(textures, shader, context, shapes);
    renderPhongHatBase(textures, shader, context, shapes);
}

void Snowman::renderPhongHatTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_hatTopTransformation);
    shader->applyMaterial(m_hatTopPrimitive.material);
    shapes[m_hatTopPrimitive.type]->draw();
}

void Snowman::renderPhongHatBase(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_hatBaseTransformation);
    shader->applyMaterial(m_hatBasePrimitive.material);
    shapes[m_hatBasePrimitive.type]->draw();
}

void Snowman::renderShadowTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_topTransformation);
    shapes[m_topPrimitive.type]->draw();
}

void Snowman::renderShadowMiddle(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_middleTransformation);
    shapes[m_middlePrimitive.type]->draw();
}

void Snowman::renderShadowBottom(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_bottomTransformation);
    shapes[m_bottomPrimitive.type]->draw();
}

void Snowman::renderShadowNose(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_noseTransformation);
    shapes[m_nosePrimitive.type]->draw();
}

void Snowman::renderShadowHat(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    renderShadowHatTop(textures, shader, context, shapes);
    renderShadowHatBase(textures, shader, context, shapes);
}

void Snowman::renderShadowHatTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_hatTopTransformation);
    shapes[m_hatTopPrimitive.type]->draw();
}


void Snowman::renderShadowHatBase(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_hatBaseTransformation);
    shapes[m_hatBasePrimitive.type]->draw();
}

void Snowman::initSnowman(){
    initSnowmanBottom();
    initSnowmanMiddle();
    initSnowmanTop();
    initSnowmanNose();
    initSnowmanHat();
}

void Snowman::initSnowmanHat(){
    initSnowmanHatTop();
    initSnowmanHatBase();
}

void Snowman::initSnowmanHatTop(){
    initSnowmanHatTopPrimitive();
    initSnowmanHatTopTransformation();
}

void Snowman::initSnowmanHatBase(){
    initSnowmanHatBasePrimitive();
    initSnowmanHatBaseTransformation();
}

void Snowman::initSnowmanNose(){
    initSnowmanNosePrimitive();
    initSnowmanNoseTransformation();
}

void Snowman::initSnowmanTop(){
    initSnowmanTopPrimitive();
    initSnowmanTopTransformation();
}

void Snowman::initSnowmanMiddle(){
    initSnowmanMiddlePrimitive();
    initSnowmanMiddleTransformation();
}

void Snowman::initSnowmanBottom(){
    initSnowmanBottomPrimitive();
    initSnowmanBottomTransformation();
}

void Snowman::initSnowmanTopPrimitive(){
    CS123ScenePrimitive top = makeSnowSphere();
    m_topPrimitive = top;
}

void Snowman::initSnowmanNosePrimitive(){
    CS123ScenePrimitive nose;
    nose.type = PrimitiveType::PRIMITIVE_CONE;
    nose.material.clear();
    nose.material.cAmbient.r = 1.f;
    nose.material.cAmbient.g = .4f;
    nose.material.cAmbient.b = .4f;
    nose.material.cDiffuse.r = 1.f;
    nose.material.cDiffuse.g = .4f;
    nose.material.cDiffuse.b = .4f;
    nose.material.cSpecular.r = nose.material.cSpecular.g = nose.material.cSpecular.b = 1;
    nose.material.shininess = 40;

    m_nosePrimitive = nose;
}

void Snowman::initSnowmanNoseTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(-m_diameterTop / 2 - m_heightNose / 2, -m_height / 2 + m_diameterBottom + m_diameterMiddle + m_diameterTop / 2, 0));
    transformation = glm::rotate(transformation, (float)M_PI / 2.f, glm::vec3(0, 0, 1));
    transformation = glm::scale(transformation, glm::vec3(m_diameterNose, m_heightNose, m_diameterNose));

    m_noseTransformation = transformation;
}

void Snowman::initSnowmanTopTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle + m_diameterTop / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterTop, m_diameterTop, m_diameterTop));

    m_topTransformation = transformation;
}

void Snowman::initSnowmanMiddlePrimitive(){
    CS123ScenePrimitive middle = makeSnowSphere();
    m_middlePrimitive = middle;
}

void Snowman::initSnowmanMiddleTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterMiddle, m_diameterMiddle, m_diameterMiddle));

    m_middleTransformation = transformation;
}

void Snowman::initSnowmanBottomPrimitive(){
    CS123ScenePrimitive bottom = makeSnowSphere();
    m_bottomPrimitive = bottom;
}

void Snowman::initSnowmanBottomTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterBottom, m_diameterBottom, m_diameterBottom));

    m_bottomTransformation = transformation;
}

CS123ScenePrimitive Snowman::makeHat(){
    CS123ScenePrimitive hat;
    hat.type = PrimitiveType::PRIMITIVE_CYLINDER;
    hat.material.clear();
    hat.material.cAmbient.r = 0.1f;
    hat.material.cAmbient.g = 0.1f;
    hat.material.cAmbient.b = 0.1f;
    hat.material.cDiffuse.r = 0.1f;
    hat.material.cDiffuse.g = 0.1f;
    hat.material.cDiffuse.b = 0.1f;
    hat.material.cSpecular.r = hat.material.cSpecular.g = hat.material.cSpecular.b = 1;
    hat.material.shininess = 100.f;

    return hat;
}

void Snowman::initSnowmanHatTopPrimitive(){
    CS123ScenePrimitive hat = makeHat();
    m_hatTopPrimitive = hat;
}

void Snowman::initSnowmanHatTopTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle + m_diameterTop + m_heightHatBase + m_heightHatTop / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterHatTop, m_heightHatTop, m_diameterHatTop));

    m_hatTopTransformation = transformation;
}

void Snowman::initSnowmanHatBasePrimitive(){
    CS123ScenePrimitive hat = makeHat();
    m_hatBasePrimitive = hat;
}

void Snowman::initSnowmanHatBaseTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle + m_diameterTop + m_heightHatBase / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterHatBase * 2, m_heightHatBase, m_diameterHatBase));

    m_hatBaseTransformation = transformation;
}

CS123ScenePrimitive Snowman::makeSnowSphere(){
    CS123ScenePrimitive snowSphere;
    snowSphere.type = PrimitiveType::PRIMITIVE_SPHERE;
    snowSphere.material.clear();
    snowSphere.material.cAmbient.r = .5f;
    snowSphere.material.cAmbient.g = .5f;
    snowSphere.material.cAmbient.b = .5f;
    snowSphere.material.cDiffuse.r = 1.f;
    snowSphere.material.cDiffuse.g = 1.f;
    snowSphere.material.cDiffuse.b = 1.f;
    snowSphere.material.cSpecular.r = snowSphere.material.cSpecular.g = snowSphere.material.cSpecular.b = 1;
    snowSphere.material.shininess = 64;

    return snowSphere;
}
