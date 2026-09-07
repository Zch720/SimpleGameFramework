#include "sgf/camera.h"
#include <sgf/rendering/camera.h>
#include <sgf/type/casting/cast_vec3.h>

namespace sgf {
    Camera::Camera(sgf_core::Camera & coreCamera):
        coreCamera(coreCamera)
    {
    }

    void Camera::update() {
        coreCamera.update();
    }
    
    void Camera::orthographicProjection(Rect size, float near, float far) {
        coreCamera.projection().setProjectionData({
            .type = sgf_core::Projection::ORTHOGRAPHIC,
            .width = size.width,
            .height = size.height,
            .near = near,
            .far = far
        });
    }
    
    void Camera::perspectiveProjection(Rect size, float near, float far, float fieldOfView) {
        coreCamera.projection().setProjectionData({
            .type = sgf_core::Projection::PERSPECTIVE,
            .width = size.width,
            .height = size.height,
            .near = near,
            .far = far,
            .fieldOfView = fieldOfView
        });
    }

    Vec3 Camera::getPosition() const {
        glm::vec3 position = coreCamera.position();
        return toSgf(position);
    }

    void Camera::setPosition(const Vec3 & position) {
        coreCamera.position(toGlm(position));
    }

    void Camera::translate(const Vec3 & delta) {
        coreCamera.translate(toGlm(delta));
    }
    
    void Camera::translateX(float delta) {
        coreCamera.translateX(delta);
    }

    void Camera::translateY(float delta) {
        coreCamera.translateY(delta);
    }

    void Camera::translateZ(float delta) {
        coreCamera.translateZ(delta);
    }

    Vec3 Camera::getRotation() const {
        glm::vec3 rotation = coreCamera.rotation();
        return toSgf(rotation);
    }

    void Camera::setRotation(const Vec3 & rotation) {
        coreCamera.rotation(toGlm(rotation));
    }

    void Camera::rotate(const Vec3 & delta) {
        coreCamera.rotate(toGlm(delta));
    }

    void Camera::rotateX(float delta) {
        coreCamera.rotateX(delta);
    }

    void Camera::rotateY(float delta) {
        coreCamera.rotateY(delta);
    }

    void Camera::rotateZ(float delta) {
        coreCamera.rotateZ(delta);
    }

}
