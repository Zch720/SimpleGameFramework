#pragma once

#include <glm/matrix.hpp>

namespace sgf_core {
    class Transform {
    private:
        bool dirty;

        glm::vec3 positionValue;
        glm::vec3 rotationValue;
        glm::vec3 scaleValue;

        glm::mat4 transformationMatrix;

        void calculateTransformationMatrix();

    public:
        Transform();

        glm::vec3 getPosition() const;

        void setPosition(const glm::vec3 & position);
        void setPositionX(float x);
        void setPositionY(float y);
        void setPositionZ(float z);

        void translate(const glm::vec3 & delta);
        void translateX(float delta);
        void translateY(float delta);
        void translateZ(float delta);

        glm::vec3 getRotation() const;

        void setRotation(const glm::vec3 & rotation);
        void setRotationX(float x);
        void setRotationY(float y);
        void setRotationZ(float z);

        void rotate(const glm::vec3 & delta);
        void rotateX(float delta);
        void rotateY(float delta);
        void rotateZ(float delta);

        glm::vec3 getScale() const;

        void setScale(const glm::vec3 & scale);
        void setScaleX(float x);
        void setScaleY(float y);
        void setScaleZ(float z);

        void scale(const glm::vec3 & delta);
        void scale(float delta);
        void scaleX(float delta);
        void scaleY(float delta);
        void scaleZ(float delta);

        void updateTransformationMatrix();
        glm::mat4 getTransformationMatrix() const;
    };
}
