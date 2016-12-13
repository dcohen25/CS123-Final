/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "camtranscamera.h"
#include <iostream>

CamtransCamera::CamtransCamera()
{
    // @TODO: [CAMTRANS] Fill this in...
    m_farPlane = 50.f;
    m_nearPlane = .1f;
    m_heightAngle = 60 * (M_PI / 180.f);
    m_aspectRatio = 1;
    m_eye = glm::vec4(0, 1, 0, 1);
    glm::vec4 look_target = glm::vec4(0, 1, -1, 1);
    glm::vec4 look = glm::normalize(look_target - m_eye);
    glm::vec4 up = glm::vec4(0, 1, 0, 0);

    m_w = -look / glm::length(look);
    m_v = (up - (glm::dot(up, m_w) * m_w)) / glm::length((up - (glm::dot(up, m_w) * m_w)));
    m_u = glm::vec4(glm::cross(glm::vec3(m_v), glm::vec3(m_w)), 0);

    updateCamera();
}

CamtransCamera::~CamtransCamera(){

}

void CamtransCamera::updateCamera(){
    updateView();
    updateProjection();
    updateFrustum();
}

void CamtransCamera::updateFrustum(){
    updateFrustumMatrix();
    updateFrustumRVectors();
    updateFrustumPlanes();
}

void CamtransCamera::updateFrustumMatrix(){
    m_frustumMatrix = m_projection * m_view;
}

void CamtransCamera::updateFrustumRVectors(){
    m_frustumR0 = glm::vec4(m_frustumMatrix[0][0], m_frustumMatrix[1][0], m_frustumMatrix[2][0], m_frustumMatrix[3][0]);
    m_frustumR1 = glm::vec4(m_frustumMatrix[0][1], m_frustumMatrix[1][1], m_frustumMatrix[2][1], m_frustumMatrix[3][1]);
    m_frustumR2 = glm::vec4(m_frustumMatrix[0][2], m_frustumMatrix[1][2], m_frustumMatrix[2][2], m_frustumMatrix[3][2]);
    m_frustumR3 = glm::vec4(m_frustumMatrix[0][3], m_frustumMatrix[1][3], m_frustumMatrix[2][3], m_frustumMatrix[3][3]);
}

void CamtransCamera::updateFrustumPlanes(){
    m_frustumLeftPlane = m_frustumR3 - m_frustumR0;
    m_frustumBottomPlane = m_frustumR3 - m_frustumR1;
    m_frustumBackPlane = m_frustumR3 - m_frustumR2;
    m_frustumRightPlane = m_frustumR3 + m_frustumR0;
    m_frustumTopPlane = m_frustumR3 + m_frustumR1;
    m_frustumFrontPlane = m_frustumR3 + m_frustumR2;
}

glm::vec4 CamtransCamera::getEye(){
    return m_eye;
}

void CamtransCamera::setAspectRatio(float a)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_aspectRatio = a;

}

bool CamtransCamera::isVisible(BoundingBox b){
    return !isBoxBehindPlane(m_frustumBackPlane, b) &&
            !isBoxBehindPlane(m_frustumFrontPlane, b) &&
            !isBoxBehindPlane(m_frustumBottomPlane, b) &&
            !isBoxBehindPlane(m_frustumTopPlane, b) &&
            !isBoxBehindPlane(m_frustumLeftPlane, b) &&
            !isBoxBehindPlane(m_frustumRightPlane, b);
}

bool CamtransCamera::isBoxBehindPlane(glm::vec4 plane, BoundingBox b){
    return isPointBehindPlane(plane, b.getBottomFaceBottomLeft()) &&
            isPointBehindPlane(plane, b.getBottomFaceBottomRight()) &&
            isPointBehindPlane(plane, b.getBottomFaceTopLeft()) &&
            isPointBehindPlane(plane, b.getTopFaceBottomLeft()) &&
            isPointBehindPlane(plane, b.getTopFaceBottomRight()) &&
            isPointBehindPlane(plane, b.getTopFaceTopLeft()) &&
            isPointBehindPlane(plane, b.getTopFaceTopRight());
}

bool CamtransCamera::isPointBehindPlane(glm::vec4 plane, glm::vec3 point){
    return plane.x * point.x +
            plane.y * point.y +
            plane.z * point.z +
            plane.w < -.4f;
}

void CamtransCamera::mouseDragged(int x, int y) {
    rotateV(.5 * x);
}

void CamtransCamera::keyDown(){
    m_eye = m_eye + (m_w * .1f);

    updateCamera();
}

void CamtransCamera::keyUp(){
    m_eye = m_eye + (-m_w * .1f);

    updateCamera();
}

void CamtransCamera::keyLeft(){
    m_eye = m_eye + (-m_u * .1f);

    updateCamera();
}

void CamtransCamera::keyRight(){
    m_eye = m_eye + (m_u * .1f);

    updateCamera();
}
void CamtransCamera::updateView(){
    glm::mat4x4 rotate(m_u[0], m_u[1], m_u[2], 0, m_v[0], m_v[1], m_v[2], 0, m_w[0], m_w[1], m_w[2], 0, 0, 0, 0, 1);
    rotate = glm::transpose(rotate);
    // set translate
    glm::mat4x4 translate(1, 0, 0, -m_eye[0], 0, 1, 0, -m_eye[1], 0, 0, 1, -m_eye[2], 0, 0, 0, 1);
    translate = glm::transpose(translate);
    // set view
    m_view = rotate * translate;
}

void CamtransCamera::updateProjection(){
    float c = -m_nearPlane / m_farPlane;
    // set perspective
    m_perspective = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, (-1 / (c + 1)), (c / (c + 1)), 0, 0, -1, 0);
    m_perspective = glm::transpose(m_perspective);
    // set scale
    m_scale = glm::mat4x4((1.f / (m_aspectRatio * tan(m_heightAngle / 2.f)) / m_farPlane), 0, 0, 0, 0, (1.f / tan(m_heightAngle / 2.f)) / m_farPlane, 0, 0, 0, 0, 1 / m_farPlane, 0, 0, 0, 0, 1);
    m_scale = glm::transpose(m_scale);
    // recompute projection
    m_projection = m_perspective * m_scale;
}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_projection;
}

glm::mat4x4 CamtransCamera::getViewMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_view;
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_scale;
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_perspective;
}

glm::vec4 CamtransCamera::getPosition() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_eye;
}

glm::vec4 CamtransCamera::getLook() const {
    // @TODO: [CAMTRANS] Fill this in...
    return -m_w;
}

glm::vec4 CamtransCamera::getUp() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_v;
}

float CamtransCamera::getAspectRatio() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_aspectRatio;
}

float CamtransCamera::getHeightAngle() const {
    // @TODO: [CAMTRANS] Fill this in...
    return m_heightAngle;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up) {
    // @TODO: [CAMTRANS] Fill this in...
    m_eye = eye;
    // set uvw
    m_w = -look / glm::length(look);
    m_v = (up - (glm::dot(up, m_w) * m_w)) / glm::length((up - (glm::dot(up, m_w) * m_w)));
    m_u = glm::vec4(glm::cross(glm::vec3(m_v), glm::vec3(m_w)), 0);

    // update view
    updateView();
    // update projection
    updateProjection();
}

void CamtransCamera::setHeightAngle(float h) {
    // @TODO: [CAMTRANS] Fill this in...
    m_heightAngle = h * (M_PI / 180.f);

    updateCamera();
}

void CamtransCamera::translate(const glm::vec4 &v) {

}

void CamtransCamera::rotateU(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float radians = degrees * (M_PI / 180.f);

    glm::vec4 u0 = m_u;
    glm::vec4 v0 = m_v;
    glm::vec4 w0 = m_w;

    m_u = u0;
    m_v = (w0 * sinf(radians)) + (v0 * cosf(radians));
    m_w = (w0 * cosf(radians)) - (v0 * sinf(radians));

    updateCamera();
}

void CamtransCamera::rotateV(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float radians = degrees * (M_PI / 180.f);

    glm::vec4 u0 = m_u;
    glm::vec4 v0 = m_v;
    glm::vec4 w0 = m_w;

    m_u = (u0 * cosf(radians)) - (w0 * sinf(radians));
    m_v = v0;
    m_w = (u0 * sinf(radians)) + (w0 * cosf(radians));

    updateCamera();
}

void CamtransCamera::rotateW(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...
    float radians = degrees * (M_PI / 180.f);

    glm::vec4 u0 = m_u;
    glm::vec4 v0 = m_v;
    glm::vec4 w0 = m_w;

    m_u = (u0 * cosf(-radians)) - (v0 * sinf(-radians));
    m_v = (u0 * sinf(-radians)) + (v0 * cosf(-radians));
    m_w = w0;

    updateCamera();
}

void CamtransCamera::setClip(float nearPlane, float farPlane) {
    // @TODO: [CAMTRANS] Fill this in...
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;

    updateCamera();
}
