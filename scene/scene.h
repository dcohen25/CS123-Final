#ifndef SCENE_H
#define SCENE_H

#include "lib/cs123scenedata.h"
class Scene
{
public:
    Scene();
    ~Scene();

protected:
    std::vector<CS123ScenePrimitive> m_primitives; // scene primitives
    std::vector<glm::mat4x4> m_transformations; // scene transformations
    std::vector<CS123SceneLightData> m_lights; // scene lights
    CS123SceneGlobalData m_global; // global data
};
#endif // SCENE_H
