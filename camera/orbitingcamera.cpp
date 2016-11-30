/**
 * @file   OrbitingCamera.cpp
 *
 * (See the header file.) You don't need to be poking around in this file unless you're interested
 * in how an orbiting camera works.
 *
 * The way we have implemented this class is NOT how you should be implementing your Camtrans. This
 * camera is a DIFFERENT TYPE of camera which we're providing so you can easily view your Shapes
 * and to make sure your scene graph is working if your camera isn't.
 *
 * In the Camtrans lab, you'll be implementing your own perspective camera from scratch! This one
 * uses OpenGL.
 */

#include <float.h>
#include <math.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <algorithm>
#include "camera/orbitingcamera.h"

OrbitingCamera::OrbitingCamera()
{
    m_aspectRatio = 1;
    m_angleX = m_angleY = 0;
    m_x = m_z = 0.f;
}

void OrbitingCamera::setAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;

    updateProjectionMatrix();
}

glm::mat4x4 OrbitingCamera::getProjectionMatrix() const {
    return m_projectionMatrix;
}

glm::mat4x4 OrbitingCamera::getViewMatrix() const {
    return m_viewMatrix;
}

glm::mat4x4 OrbitingCamera::getScaleMatrix() const {
    return m_scaleMatrix;
}

void OrbitingCamera::mouseDown(int x, int y) {
    m_oldX = x;
    m_oldY = y;
}

void OrbitingCamera::mouseDragged(int x, int y) {
    m_angleY += x - m_oldX;
    m_angleX += y - m_oldY;
    m_oldX = x;
    m_oldY = y;
    if (m_angleX < -90) m_angleX = -90;
    if (m_angleX > 90) m_angleX = 90;

    float radians = m_angleX * (M_PI / 180.f);

    glm::vec4 u0 = m_u;
    glm::vec4 v0 = m_v;
    glm::vec4 w0 = m_w;

    m_u = u0;
    m_v = (w0 * sinf(radians)) + (v0 * cosf(radians));
    m_w = (w0 * cosf(radians)) - (v0 * sinf(radians));

    radians = m_angleY * (M_PI / 180.f);

    u0 = m_u;
    v0 = m_v;
    w0 = m_w;

    m_u = (u0 * cosf(radians)) - (w0 * sinf(radians));
    m_v = v0;
    m_w = (u0 * sinf(radians)) + (w0 * cosf(radians));

    updateViewMatrix();
    // update projection
    updateProjection();
}

void OrbitingCamera::keyDown(){
    m_z -= .1;
    updateViewMatrix();
}

void OrbitingCamera::keyUp(){
    m_z += .1;
    updateViewMatrix();
}

void OrbitingCamera::keyLeft(){
    m_x += .1;
    updateViewMatrix();
}

void OrbitingCamera::keyRight(){
    m_x -= .1;
    updateViewMatrix();
}

void OrbitingCamera::updateMatrices() {
    updateProjectionMatrix();
    updateViewMatrix();
}

void OrbitingCamera::updateProjectionMatrix() {
    // Make sure glm gets a far value that is greater than the near value.
    // Thanks Windows for making far a keyword!
    float farPlane = std::max(50.f, .1f + 100.f * FLT_EPSILON);
    float h = farPlane * glm::tan(glm::radians(50.f/2));
    float w = m_aspectRatio * h;
    m_scaleMatrix = glm::scale(glm::vec3(1.f/w, 1.f/h, 1.f/farPlane));
    m_projectionMatrix = glm::perspective(
            glm::radians(50.f), m_aspectRatio, .1f, 50.f) / 50.f;
}

void OrbitingCamera::updateViewMatrix() {
    m_viewMatrix =
            glm::translate(glm::vec3(m_x, 0.f, m_z)) *
            glm::rotate(glm::radians(m_angleY), glm::vec3(0.f, 1.f, 0.f)) *
            glm::rotate(glm::radians(m_angleX), glm::vec3(1.f, 0.f, 0.f));
}
