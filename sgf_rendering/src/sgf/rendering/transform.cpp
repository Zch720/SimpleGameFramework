#include "sgf/rendering/transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sgf_core {
    Transform::Transform():
        dirty(false),
        positionValue(0.0),
        rotationValue(0.0),
        scaleValue(1.0),
        transformationMatrix(1.0)
    {
    }
    
    glm::vec3 Transform::getPosition() const {
        return positionValue;
    }

    void Transform::setPosition(const glm::vec3 & position) {
        positionValue = position;
        dirty = true;
    }

    void Transform::setPositionX(float x) {
        positionValue.x = x;
        dirty = true;
    }

    void Transform::setPositionY(float y) {
        positionValue.y = y;
        dirty = true;
    }

    void Transform::setPositionZ(float z) {
        positionValue.z = z;
        dirty = true;
    }

    void Transform::translate(const glm::vec3 & delta) {
        positionValue += delta;
        dirty = true;
    }

    void Transform::translateX(float delta) {
        positionValue.x += delta;
        dirty = true;
    }

    void Transform::translateY(float delta) {
        positionValue.y += delta;
        dirty = true;
    }

    void Transform::translateZ(float delta) {
        positionValue.z = delta;
        dirty = true;
    }

    glm::vec3 Transform::getRotation() const {
        return rotationValue;
    }

    void Transform::setRotation(const glm::vec3 & rotation) {
        rotationValue = rotation;
        dirty = true;
    }

    void Transform::setRotationX(float x) {
        rotationValue.x = x;
        dirty = true;
    }

    void Transform::setRotationY(float y) {
        rotationValue.y = y;
        dirty = true;
    }

    void Transform::setRotationZ(float z) {
        rotationValue.z = z;
        dirty = true;
    }

    void Transform::rotate(const glm::vec3 & delta) {
        rotationValue += delta;
        dirty = true;
    }

    void Transform::rotateX(float delta) {
        rotationValue.x += delta;
        dirty = true;
    }

    void Transform::rotateY(float delta) {
        rotationValue.y += delta;
        dirty = true;
    }

    void Transform::rotateZ(float delta) {
        rotationValue.z += delta;
        dirty = true;
    }

    glm::vec3 Transform::getScale() const {
        return scaleValue;
    }

    void Transform::setScale(const glm::vec3 & scale) {
        scaleValue = scale;
        dirty = true;
    }

    void Transform::setScaleX(float x) {
        scaleValue.x = x;
        dirty = true;
    }

    void Transform::setScaleY(float y) {
        scaleValue.y = y;
        dirty = true;
    }

    void Transform::setScaleZ(float z) {
        scaleValue.z = z;
        dirty = true;
    }

    void Transform::scale(const glm::vec3 & delta) {
        scaleValue *= delta;
        dirty = true;
    }

    void Transform::scale(float delta) {
        scaleValue *= delta;
        dirty = true;
    }

    void Transform::scaleX(float delta) {
        scaleValue.x *= delta;
        dirty = true;
    }

    void Transform::scaleY(float delta) {
        scaleValue.y *= delta;
        dirty = true;
    }

    void Transform::scaleZ(float delta) {
        scaleValue.z *= delta;
        dirty = true;
    }

    void Transform::updateTransformationMatrix() {
        if (dirty) {
            calculateTransformationMatrix();
            dirty = false;
        }
    }

    glm::mat4 Transform::getTransformationMatrix() const {
        return transformationMatrix;
    }

    void Transform::calculateTransformationMatrix() {
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, glm::radians(rotationValue.x), glm::vec3(1.0f, 0.0f, 0.0f));
        mat = glm::rotate(mat, glm::radians(rotationValue.y), glm::vec3(0.0f, 1.0f, 0.0f));
        mat = glm::rotate(mat, glm::radians(rotationValue.z), glm::vec3(0.0f, 0.0f, 1.0f));
        mat = glm::translate(mat, positionValue);
        mat = glm::scale(mat, scaleValue);
        transformationMatrix = mat;
    }
}
