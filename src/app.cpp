#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include <../include/glm/glm.hpp>
#include <../include/glm/gtc/matrix_transform.hpp>
#include <../include/glm/gtc/type_ptr.hpp>

#include "window.h"
#include "vertex.h"
#include "shader.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

static float x = 0;
static float z = 0;

void cleanup() {
    glfwTerminate();
}

void process_input(Core::Window& window) {
    if (glfwGetKey(window.get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window.get_window(), true);
    } if (glfwGetKey(window.get_window(), GLFW_KEY_S) == GLFW_PRESS) {
        z -= 0.02;
    } if (glfwGetKey(window.get_window(), GLFW_KEY_W) == GLFW_PRESS) {
        z += 0.02;
    } if (glfwGetKey(window.get_window(), GLFW_KEY_A) == GLFW_PRESS) {
        x += 0.02;
    } if (glfwGetKey(window.get_window(), GLFW_KEY_D) == GLFW_PRESS) {
        x -= 0.02;
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

    /*
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  // top left
    };*/
    /*
    Core::Vertex vertices[] = {
        Core::Vertex{0.5f, 0.5f, 0.0f},
        Core::Vertex{0.5f, -0.5f, 0.0f},
        Core::Vertex{-0.5f, -0.5f, 0.0f},
        Core::Vertex{-0.5f, 0.5f, 0.0f},
    };*/
    Core::Vertex vertices[] = {
        {0.0f, 0.5f, 0.0f},     // top
        {0.5f, -0.5f, 0.5f},    // front right
        {-0.5f, -0.5f, 0.5f},   // front left
        {-0.5f, -0.5f, -0.5f},  // back left
        {0.5f, -0.5f, -0.5f},   // back right
    };

    unsigned int indices[] = {
        0, 1, 2,    // front triangle
        0, 2, 3,    // left triangle
        0, 1, 4,    // right triangle
        0, 3, 4,    // back triangle
        2, 3, 4,    // bot triangle left
        1, 2, 4,    // bot triangle right
    };

    // Prepare data for rendering this object.
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Setup shaders
    Core::Shader shader {std::string{"src/current"}};
    shader.bind();
    
    gameWindow.show();

    GLFWwindow* main_window {gameWindow.get_window()};
    while (!glfwWindowShouldClose(main_window)) {
        // input handling
        process_input(gameWindow);

        // rendering
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // z-buffer
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();

        // change color
        float curTime = glfwGetTime();
        float greenValue = (sin(curTime) / 2.0f) + 0.5f;
        shader.setVec4("uColor", glm::vec4(0.0f, greenValue, 0.0f, 1.0f));

        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 0.0f, z));
        shader.setMat4("uModel", modelMatrix);

        glm::mat4 viewMatrix;
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
        shader.setMat4("uView", viewMatrix);

        glm::mat4 projMatrix;
        projMatrix = glm::perspective(glm::radians(45.0f), 
            (float)gameWindow.getWidth() / (float)gameWindow.getHeight(), 0.1f, 100.0f);
        shader.setMat4("uProj", projMatrix);

        /*
        // translation
        glm::mat4 trans;
        trans = glm::translate(trans, glm::vec3(sin(curTime) / 2.0f, cos(curTime) / 2.0f, 0.0f));
        trans = glm::scale(trans, glm::vec3(sin(curTime) / 4.0f + 1.0f, sin(curTime) / 4.0f + 1.0f, 1.0f));
        shader.setMat4("uTrans", trans);
        */

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        // check/call events and swap buffers
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    std::cout << "Closing app..." << std::endl;

    cleanup();

    return 0;
}