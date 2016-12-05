#include "snowman.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "snowscene.h"


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

void Snowman::initSnowman(){
    initSnowmanBody();
    initSnowmanHat();
}

void Snowman::initSnowmanBody(){
    initSnowmanBottom();
    initSnowmanMiddle();
    initSnowmanTop();
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

void Snowman::initSnowmanTop(){
    initSnowmanTopHead();
    initSnowmanTopNose();
}

void Snowman::initSnowmanTopNose(){
    initSnowmanTopNosePrimitive();
    initSnowmanTopNoseTransformation();
}

void Snowman::initSnowmanTopHead(){
    initSnowmanTopHeadPrimitive();
    initSnowmanTopHeadTransformation();
}

void Snowman::initSnowmanMiddle(){
    initSnowmanMiddlePrimitive();
    initSnowmanMiddleTransformation();
}

void Snowman::initSnowmanBottom(){
    initSnowmanBottomPrimitive();
    initSnowmanBottomTransformation();
}

void Snowman::initSnowmanTopHeadPrimitive(){
    CS123ScenePrimitive top = makeSnowSphere();
    m_primitives.push_back(top);
}

void Snowman::initSnowmanTopNosePrimitive(){
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

    m_primitives.push_back(nose);
}

void Snowman::initSnowmanTopNoseTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle + m_diameterTop / 2, m_diameterTop / 2 + m_heightNose / 2));
    transformation = glm::rotate(transformation, (float)M_PI / 2.f, glm::vec3(1, 0, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterNose, m_heightNose, m_diameterNose));

    m_transformations.push_back(transformation);
}

void Snowman::initSnowmanTopHeadTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle + m_diameterTop / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterTop, m_diameterTop, m_diameterTop));

    m_transformations.push_back(transformation);
}

void Snowman::initSnowmanMiddlePrimitive(){
    CS123ScenePrimitive middle = makeSnowSphere();
    m_primitives.push_back(middle);
}

void Snowman::initSnowmanMiddleTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterMiddle, m_diameterMiddle, m_diameterMiddle));

    m_transformations.push_back(transformation);
}

void Snowman::initSnowmanBottomPrimitive(){
    CS123ScenePrimitive bottom = makeSnowSphere();
    m_primitives.push_back(bottom);
}

void Snowman::initSnowmanBottomTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterBottom, m_diameterBottom, m_diameterBottom));

    m_transformations.push_back(transformation);
}

CS123ScenePrimitive Snowman::makeHat(){
    CS123ScenePrimitive hat;
    hat.type = PrimitiveType::PRIMITIVE_CYLINDER;
    hat.material.clear();
    hat.material.cAmbient.r = 0.f;
    hat.material.cAmbient.g = 0.f;
    hat.material.cAmbient.b = 0.f;
    hat.material.cDiffuse.r = 0.f;
    hat.material.cDiffuse.g = 0.f;
    hat.material.cDiffuse.b = 0.f;
    hat.material.cSpecular.r = hat.material.cSpecular.g = hat.material.cSpecular.b = 1;
    hat.material.shininess = 100.f;

    return hat;
}

void Snowman::initSnowmanHatTopPrimitive(){
    CS123ScenePrimitive hat = makeHat();
    m_primitives.push_back(hat);
}

void Snowman::initSnowmanHatTopTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle + m_diameterTop + m_heightHatBase + m_heightHatTop / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterHatTop, m_heightHatTop, m_diameterHatTop));

    m_transformations.push_back(transformation);
}

void Snowman::initSnowmanHatBasePrimitive(){
    CS123ScenePrimitive hat = makeHat();
    m_primitives.push_back(hat);
}

void Snowman::initSnowmanHatBaseTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, m_coords);
    transformation = glm::translate(transformation, glm::vec3(0, -m_height / 2 + m_diameterBottom + m_diameterMiddle + m_diameterTop + m_heightHatBase / 2, 0));
    transformation = glm::scale(transformation, glm::vec3(m_diameterHatBase * 2, m_heightHatBase, m_diameterHatBase));

    m_transformations.push_back(transformation);
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
