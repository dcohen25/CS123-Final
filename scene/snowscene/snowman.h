#ifndef SNOWMAN_H
#define SNOWMAN_H

#include "snowsceneobject.h"
#include "gl/textures/Texture2D.h"

class Snowman : public SnowSceneObject
{
public:
    Snowman(glm::vec3 coords, float diameter, float speed, glm::vec3 direction);
    Snowman();
    ~Snowman();

    static float computeSnowmanHeight(float diameter);

    virtual void makeObject() override;

    virtual void renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) override;
    virtual void renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) override;

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
    void initSnowmanTop();
    void initSnowmanMiddle();
    void initSnowmanBottom();
    void initSnowmanNose();
    void initSnowmanHat();
    void initSnowmanHatTop();
    void initSnowmanHatBase();
    void initSnowmanNosePrimitive();
    void initSnowmanTopPrimitive();
    void initSnowmanMiddlePrimitive();
    void initSnowmanBottomPrimitive();
    void initSnowmanHatTopPrimitive();
    void initSnowmanHatBasePrimitive();
    void initSnowmanNoseTransformation();
    void initSnowmanTopTransformation();
    void initSnowmanMiddleTransformation();
    void initSnowmanBottomTransformation();
    void initSnowmanHatTopTransformation();
    void initSnowmanHatBaseTransformation();

    void renderShadowTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderShadowMiddle(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderShadowBottom(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderShadowNose(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderShadowHat(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderShadowHatTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderShadowHatBase(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);

    void renderPhongTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderPhongMiddle(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderPhongBottom(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderPhongNose(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderPhongHat(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderPhongHatTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderPhongHatBase(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);

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

    CS123ScenePrimitive m_hatTopPrimitive;
    CS123ScenePrimitive m_hatBasePrimitive;
    CS123ScenePrimitive m_nosePrimitive;
    CS123ScenePrimitive m_topPrimitive;
    CS123ScenePrimitive m_middlePrimitive;
    CS123ScenePrimitive m_bottomPrimitive;

    glm::mat4x4 m_hatTopTransformation;
    glm::mat4x4 m_hatBaseTransformation;
    glm::mat4x4 m_noseTransformation;
    glm::mat4x4 m_topTransformation;
    glm::mat4x4 m_middleTransformation;
    glm::mat4x4 m_bottomTransformation;

};



#endif // SNOWMAN_H
