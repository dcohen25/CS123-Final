#ifndef ORBITINGCAMERA_H
#define ORBITINGCAMERA_H

#include "camera.h"

/**
 * @class OrbitingCamera
 *
 * Camera that move in response to mouse interaction.
 *
 * You shouldn't need to work on this class. It's there for your convenience, really,
 * and the way this camera is implemented is NOT the way you should be implementing
 * your camera in the Camtrans lab. We hide the real implementation by using OpenGL to
 * perform the camera calculations.
 *
 */
class OrbitingCamera : public Camera {
public:
    OrbitingCamera();

    virtual void setAspectRatio(float aspectRatio);

    virtual glm::mat4x4 getProjectionMatrix() const;
    virtual glm::mat4x4 getViewMatrix() const;
    virtual glm::mat4x4 getScaleMatrix() const;

    virtual void mouseDown(int x, int y);
    virtual void mouseDragged(int x, int y);
    virtual void keyDown();
    virtual void keyLeft();
    virtual void keyUp();
    virtual void keyRight();

    // Translates the camera along a given vector.
    void translate(const glm::vec4 &v);

    // Rotates the camera about the U axis by a specified number of degrees.
    void rotateU(float degrees);

    // Rotates the camera about the V axis by a specified number of degrees.
    void rotateV(float degrees);

    // Rotates the camera about the W axis by a specified number of degrees.
    void rotateW(float degrees);

    // Sets the near and far clip planes for this camera.
    void setClip(float nearPlane, float farPlane);

    void updateMatrices();

private:
    void updateProjectionMatrix();
    void updateViewMatrix();

    float m_angleX, m_angleY;
    int m_oldX, m_oldY;
    float m_x, m_z;
    glm::mat4x4 m_projection;
    glm::mat4x4 m_view;
    glm::mat4x4 m_scale;
    glm::mat4x4 m_perspective;
    float m_aspectRatio;
    float m_heightAngle;
    float m_nearPlane;
    float m_farPlane;
    glm::vec4 m_u;
    glm::vec4 m_v;
    glm::vec4 m_w;
    glm::vec4 m_eye;
};

#endif // ORBITINGCAMERA_H
