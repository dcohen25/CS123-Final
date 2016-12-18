#ifndef SNOW_H
#define SNOW_H

#include "snowsceneobject.h"

class Snow : public SnowSceneObject
{
public:
    Snow(glm::vec3 coords);
    ~Snow();

    virtual void renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes) override;
    virtual void renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes) override;

    virtual void makeObject() override;
protected:
    void initSnowPrimitive();
    void initSnowTransformation();

    CS123ScenePrimitive m_snowPrimitive;
    glm::mat4x4 m_snowTransformation;
};

#endif // SNOW_H
