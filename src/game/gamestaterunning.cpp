#include "gamestaterunning.h"

#include <iostream>

using namespace Game;



GameStateRunning::GameStateRunning(Core::Window& window, Core::Camera& camera) 
    :m_window{window}, m_camera{camera}
{

}

GameStateRunning::~GameStateRunning() {}

void GameStateRunning::handleInput() {
    GLFWwindow* window {m_window.get_window()};
    std::cout << "input!" << std::endl;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_camera.moveBackward();
    } if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_camera.moveForward();
    } if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_camera.moveLeft();
    } if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_camera.moveRight();
    } if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        m_camera.rotateLeft();
    } if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        m_camera.rotateRight();
    }
}

void GameStateRunning::handleEvent() {}

void GameStateRunning::update(float deltaTime) {
    m_camera.update();
}

void GameStateRunning::render() {}
