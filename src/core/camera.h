#ifndef CAMERA_H
#define CAMERA_H

#include <../../include/glm/glm.hpp>
#include <../../include/glm/gtc/matrix_transform.hpp>
#include <../../include/glm/gtc/type_ptr.hpp>

namespace Core {
    class Camera {
        public:
            Camera() :Camera{glm::vec3(0.0f, 0.0f, 3.0f)} {};
            Camera(glm::vec3 start);
            virtual ~Camera();
            void update();
            glm::vec3 getViewPos();
            glm::mat4 getViewMatrix();
            void moveForward();
            void moveBackward();
            void moveRight();
            void moveLeft();
            void rotateRight();
            void rotateLeft();
        private:
            glm::vec3 m_cameraPos;
            glm::vec3 m_cameraFront;
            glm::vec3 m_cameraUp;
            float m_baseCameraSpeed;
            float m_cameraSpeed;
            double m_lastFrame;
            float m_pitch;
            float m_yaw;

            void rotate(float delta_yaw);
            void updateSpeed();
    };
};

#endif