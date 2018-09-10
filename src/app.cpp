#include "gl_header.h"

#include "window.h"
#include "vertex.h"
#include "shader.h"
#include "camera.h"
#include "mesh.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>



void cleanup() {
    glfwTerminate();
}

void process_input(Core::Window& window, Core::Camera& camera) {
    if (glfwGetKey(window.get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window.get_window(), true);
    } if (glfwGetKey(window.get_window(), GLFW_KEY_S) == GLFW_PRESS) {
        camera.moveBackward();
    } if (glfwGetKey(window.get_window(), GLFW_KEY_W) == GLFW_PRESS) {
        camera.moveForward();
    } if (glfwGetKey(window.get_window(), GLFW_KEY_A) == GLFW_PRESS) {
        camera.moveLeft();
    } if (glfwGetKey(window.get_window(), GLFW_KEY_D) == GLFW_PRESS) {
        camera.moveRight();
    } if (glfwGetKey(window.get_window(), GLFW_KEY_Q) == GLFW_PRESS) {
        camera.rotateLeft();
    } if (glfwGetKey(window.get_window(), GLFW_KEY_E) == GLFW_PRESS) {
        camera.rotateRight();
    }
}

int main(int argc, char **argv) {
    
    glfwInit();
    
    Core::Window gameWindow {800, 600, "My First OpenGL Window"};

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: Failed to initialize GLAD!" << std::endl;
        cleanup();
        return -1;
    }

    std::vector<Core::Vertex> verticesPyramid {
        {0.0f, 0.5f, 0.0f},     // top
        {0.5f, -0.5f, 0.5f},    // front right
        {-0.5f, -0.5f, 0.5f},   // front left
        {-0.5f, -0.5f, -0.5f},  // back left
        {0.5f, -0.5f, -0.5f},   // back right
    };

    std::vector<unsigned int> indicesPyramid {
        0, 1, 2,    // front triangle
        0, 2, 3,    // left triangle
        0, 1, 4,    // right triangle
        0, 3, 4,    // back triangle
        2, 3, 4,    // bot triangle left
        1, 2, 4,    // bot triangle right
    };


    // Setup shaders
    Core::Shader objectShader {std::string{"src/shaders/current"}};
    Core::Shader lampShader {std::string{"src/shaders/current_lamp"}};
    
    Core::Camera camera {};

    Core::Mesh lamp {verticesPyramid, indicesPyramid};
    Core::Mesh mesh {verticesPyramid, indicesPyramid};

    gameWindow.show();

    GLFWwindow* main_window {gameWindow.get_window()};
    while (!glfwWindowShouldClose(main_window)) {
        // input handling
        process_input(gameWindow, camera);

        // rendering
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // z-buffer
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        camera.update();

        // change color
        objectShader.bind();

        float curTime = glfwGetTime();
        float greenValue = (sin(curTime) / 2.0f) + 0.5f;
        objectShader.setVec4("uObjectColor", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        objectShader.setVec4("uLightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, 0.0f, 0.0f));
        objectShader.setMat4("uModel", modelMatrix);

        glm::mat4 viewMatrix;
        //viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
        viewMatrix = camera.getViewMatrix();
        objectShader.setMat4("uView", viewMatrix);

        glm::mat4 projMatrix;
        projMatrix = glm::perspective(glm::radians(45.0f), 
            (float)gameWindow.getWidth() / (float)gameWindow.getHeight(), 0.1f, 100.0f);
        objectShader.setMat4("uProj", projMatrix);

        mesh.bind();
        mesh.draw();
        mesh.unbind();


        lampShader.bind();

        glm::vec3 lampPos {glm::vec3(1.2f, 1.0f, 2.0f)};
        glm::mat4 lampModelMatrix {};
        lampModelMatrix = glm::translate(lampModelMatrix, lampPos);
        lampModelMatrix = glm::scale(lampModelMatrix, glm::vec3(0.2f));
        lampShader.setMat4("uModel", lampModelMatrix);
        lampShader.setMat4("uView", viewMatrix);
        lampShader.setMat4("uProj", projMatrix);

        lamp.bind();
        lamp.draw();
        lamp.unbind();

        // check/call events and swap buffers
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }

    std::cout << "Closing app..." << std::endl;

    cleanup();

    return 0;
}