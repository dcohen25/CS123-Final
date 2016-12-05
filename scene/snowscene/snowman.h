#ifndef SNOWMAN_H
#define SNOWMAN_H

#include "snowsceneobject.h"

class Snowman : public SnowSceneObject
{
public:
    Snowman(glm::vec3 coords, float diameter);
    Snowman();
    ~Snowman();

    static float computeSnowmanHeight(float diameter);

    const static float maxDiameter;
    const static float m_diameterBottomProportion;
    const static float m_diameterMiddleProportion;
    const static float m_diameterTopProportion;
    const static float m_diameterHatBaseProportion;
    const static float m_diameterHatTopProportion;
    const static float m_diameterNoseProportion;
    const static float m_heightHatBaseProportion;
    const static float m_heightHatTopProportion;
    const static float m_heightNoseProportion;

protected:
    void initSnowman();
    void initSnowmanBody();
    void initSnowmanTop();
    void initSnowmanTopHead();
    void initSnowmanTopNose();
    void initSnowmanMiddle();
    void initSnowmanBottom();
    void initSnowmanHat();
    void initSnowmanHatTop();
    void initSnowmanHatBase();
    void initSnowmanTopNosePrimitive();
    void initSnowmanTopHeadPrimitive();
    void initSnowmanMiddlePrimitive();
    void initSnowmanBottomPrimitive();
    void initSnowmanHatTopPrimitive();
    void initSnowmanHatBasePrimitive();
    void initSnowmanTopNoseTransformation();
    void initSnowmanTopHeadTransformation();
    void initSnowmanMiddleTransformation();
    void initSnowmanBottomTransformation();
    void initSnowmanHatTopTransformation();
    void initSnowmanHatBaseTransformation();

    CS123ScenePrimitive makeSnowSphere();
    CS123ScenePrimitive makeHat();

    float m_diameterTop;
    float m_diameterMiddle;
    float m_diameterBottom;
    float m_diameterHatBase;
    float m_diameterHatTop;
    float m_diameterNose;
    float m_heightHatBase;
    float m_heightHatTop;
    float m_heightNose;
};

#endif // SNOWMAN_H
