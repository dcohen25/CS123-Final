#ifndef SNOW_H
#define SNOW_H

#include "snowsceneobject.h"

class Snow : public SnowSceneObject
{
public:
    Snow(glm::vec3 coords);
    ~Snow();
protected:
    void initSnow();
    void initSnowPrimitive();
    void initSnowTransformation();
};

#endif // SNOW_H
