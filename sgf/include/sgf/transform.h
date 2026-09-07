#pragma once

#include <sgf/type/vec3.h>

namespace sgf_core {
    class Transform;
}

namespace sgf {
    class Transform {
    private:
        sgf_core::Transform & coreTransform;

    public:
        Transform(sgf_core::Transform & coreTransform);

        Vec3 getPosition() const;

        void setPosition(const Vec3 & position);
        void setPositionX(float x);
        void setPositionY(float y);
        void setPositionZ(float z);

        void translate(const Vec3 & delta);
        void translateX(float delta);
        void translateY(float delta);
        void translateZ(float delta);

        Vec3 getRotation() const;

        void setRotation(const Vec3 & rotation);
        void setRotationX(float x);
        void setRotationY(float y);
        void setRotationZ(float z);

        void rotate(const Vec3 & delta);
        void rotateX(float delta);
        void rotateY(float delta);
        void rotateZ(float delta);

        Vec3 getScale() const;

        void setScale(const Vec3 & scale);
        void setScaleX(float x);
        void setScaleY(float y);
        void setScaleZ(float z);

        void scale(const Vec3 & delta);
        void scale(float delta);
        void scaleX(float delta);
        void scaleY(float delta);
        void scaleZ(float delta);

        void update();
    };
}
