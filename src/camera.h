#ifndef CAMERA_H
#define CAMERA_H

#include <../include/glm/glm.hpp>

namespace Core {
    class Camera {
        public:
            Camera() :Camera{glm::vec3(0.0f, 0.0f, 3.0f)} {};
            Camera(glm::vec3 start);
            virtual ~Camera();
            void update();
            glm::mat4 getViewMatrix();
            void moveForward();
            void moveBackward();
            void moveRight();
            void moveLeft();
        private:
            glm::vec3 m_cameraPos;
            glm::vec3 m_cameraFront;
            glm::vec3 m_cameraUp;
            float m_baseCameraSpeed;
            float m_cameraSpeed;
            float m_lastFrame;

            void updateSpeed();
    };
};

#endif