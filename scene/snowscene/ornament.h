#ifndef ORNAMENT_H
#define ORNAMENT_H

#include "snowsceneobject.h"

class Ornament : public SnowSceneObject
{
public:
    Ornament(glm::vec3 coords);
    ~Ornament();

    virtual void renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes) override;
    virtual void renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes) override;

    virtual void makeObject() override;
protected:
    void initOrnamentTop();
    void initOrnamentBottom();
    void initOrnamentTopPrimitive();
    void initOrnamentTopTransformation();
    void initOrnamentBottomPrimitive();
    void initOrnamentBottomTransformation();
    void initColors();
    void setColor();
    void renderPhongSceneTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes);
    void renderShadowSceneTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes);
    void renderPhongSceneBottom(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes);
    void renderShadowSceneBottom(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes);

    std::vector<glm::vec3> m_colors;
    glm::vec3 m_color;

    const static float bottomDiameter;
    const static float topHeight;
    const static float topDiameter;

    CS123ScenePrimitive m_ornamentTopPrimitive;
    glm::mat4x4 m_ornamentTopTransformation;
    CS123ScenePrimitive m_ornamentBottomPrimitive;
    glm::mat4x4 m_ornamentBottomTransformation;
};

#endif // SNOW_H
