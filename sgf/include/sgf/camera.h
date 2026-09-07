#pragma once

#include <sgf/type/vec3.h>
#include <sgf/type/rect.h>

namespace sgf_core {
    class Camera;
}

namespace sgf {
    class Game;

    class Camera {
    private:
        friend Game;

        sgf_core::Camera & coreCamera;

        Camera(sgf_core::Camera & coreCamera);

    public:
        void update();

        void orthographicProjection(Rect size, float near, float far);
        void perspectiveProjection(Rect size, float near, float far, float fieldOfView);

        Vec3 getPosition() const;
        void setPosition(const Vec3 & position);
        void translate(const Vec3 & delta);
        void translateX(float delta);
        void translateY(float delta);
        void translateZ(float delta);

        Vec3 getRotation() const;
        void setRotation(const Vec3 & rotation);
        void rotate(const Vec3 & delta);
        void rotateX(float delta);
        void rotateY(float delta);
        void rotateZ(float delta);
    };
}
