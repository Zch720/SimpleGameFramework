#include "sgf/transform.h"
#include <sgf/rendering/transform.h>
#include <sgf/type/casting/cast_vec3.h>

namespace sgf {
    Transform::Transform(sgf_core::Transform & coreTransform):
        coreTransform(coreTransform)
    {
    }

    Vec3 Transform::getPosition() const {
        return toSgf(coreTransform.getPosition());
    }

    void Transform::setPosition(const Vec3 & position) {
        coreTransform.setPosition(toGlm(position));
    }

    void Transform::setPositionX(float x) {
        coreTransform.setPositionX(x);
    }

    void Transform::setPositionY(float y) {
        coreTransform.setPositionY(y);
    }

    void Transform::setPositionZ(float z) {
        coreTransform.setPositionZ(z);
    }

    void Transform::translate(const Vec3 & delta) {
        coreTransform.translate(toGlm(delta));
    }

    void Transform::translateX(float delta) {
        coreTransform.translateX(delta);
    }

    void Transform::translateY(float delta) {
        coreTransform.translateY(delta);
    }

    void Transform::translateZ(float delta) {
        coreTransform.translateZ(delta);
    }

    Vec3 Transform::getRotation() const {
        return toSgf(coreTransform.getRotation());
    }

    void Transform::setRotation(const Vec3 & rotation) {
        coreTransform.setRotation(toGlm(rotation));
    }

    void Transform::setRotationX(float x) {
        coreTransform.setRotationX(x);
    }

    void Transform::setRotationY(float y) {
        coreTransform.setRotationY(y);
    }

    void Transform::setRotationZ(float z) {
        coreTransform.setRotationZ(z);
    }

    void Transform::rotate(const Vec3 & delta) {
        coreTransform.rotate(toGlm(delta));
    }

    void Transform::rotateX(float delta) {
        coreTransform.rotateX(delta);
    }

    void Transform::rotateY(float delta) {
        coreTransform.rotateY(delta);
    }

    void Transform::rotateZ(float delta) {
        coreTransform.rotateZ(delta);
    }

    Vec3 Transform::getScale() const {
        return toSgf(coreTransform.getScale());
    }

    void Transform::setScale(const Vec3 & scale) {
        coreTransform.setScale(toGlm(scale));
    }

    void Transform::setScaleX(float x) {
        coreTransform.setScaleX(x);
    }

    void Transform::setScaleY(float y) {
        coreTransform.setScaleY(y);
    }

    void Transform::setScaleZ(float z) {
        coreTransform.setScaleZ(z);
    }

    void Transform::scale(const Vec3 & delta) {
        coreTransform.scale(toGlm(delta));
    }

    void Transform::scale(float delta) {
        coreTransform.scale(delta);
    }

    void Transform::scaleX(float delta) {
        coreTransform.scaleX(delta);
    }

    void Transform::scaleY(float delta) {
        coreTransform.scaleY(delta);
    }

    void Transform::scaleZ(float delta) {
        coreTransform.scaleZ(delta);
    }

    void Transform::update() {
        coreTransform.updateTransformationMatrix();
    }
}
