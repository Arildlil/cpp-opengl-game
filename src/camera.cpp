#include "camera.h"

#include "../include/GLFW/glfw3.h"

#include <../include/glm/glm.hpp>
#include <../include/glm/gtc/matrix_transform.hpp>
#include <../include/glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace Core;



Camera::Camera(glm::vec3 startPos) 
    :m_cameraPos{startPos}, m_cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)}, 
     m_cameraUp{glm::vec3(0.0, 1.0f, 0.0f)}, m_baseCameraSpeed{2.5f}, 
     m_cameraSpeed{2.5f}, m_lastFrame{0.0f}
{
    
}

Camera::~Camera() {}

void Camera::update() {
    updateSpeed();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void Camera::moveForward() {
    m_cameraPos += m_cameraSpeed * m_cameraFront;
}

void Camera::moveBackward() {
    m_cameraPos -= m_cameraSpeed * m_cameraFront;
}

void Camera::moveRight() {
    m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed;
}

void Camera::moveLeft() {
    m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed;
}

void Camera::updateSpeed() {
    float currentFrame {glfwGetTime()};
    float deltaTime {currentFrame - m_lastFrame};
    m_lastFrame = currentFrame;
    m_cameraSpeed = m_baseCameraSpeed * deltaTime;
    std::cout << "delta: " << deltaTime << ", speed: " << m_cameraSpeed << std::endl;
}