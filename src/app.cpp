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



void cleanup() {
    glfwTerminate();
}

void process_input(Core::Window& window) {
    if (glfwGetKey(window.get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window.get_window(), true);
    }
}

int main(int argc, char **argv) {
    
    glfwInit();
    
    Core::Window game_window {800, 600, "My First OpenGL Window"};

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
        {0.0f, 0.5f, 0.0f},
        {0.5f, -0.5f, 0.5f},
        {-0.5f, -0.5f, 0.5f},
    };

    unsigned int indices[] = {
        0, 1, 2,    // first triangle
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

    game_window.show();

    GLFWwindow* main_window {game_window.get_window()};
    while (!glfwWindowShouldClose(main_window)) {
        // input handling
        process_input(game_window);

        // rendering
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        // change color
        float curTime = glfwGetTime();
        float greenValue = (sin(curTime) / 2.0f) + 0.5f;
        int vertexColorLoc = shader.getTransformLoc("uColor");
        glUniform4f(vertexColorLoc, 0.0f, greenValue, 0.0f, 1.0f);

        /*
        // translation
        glm::mat4 trans;
        trans = glm::translate(trans, glm::vec3(sin(curTime) / 2.0f, cos(curTime) / 2.0f, 0.0f));
        trans = glm::scale(trans, glm::vec3(sin(curTime) / 4.0f + 1.0f, sin(curTime) / 4.0f + 1.0f, 1.0f));
        */
        glm::mat4 trans;
        unsigned int transLoc = shader.getTransformLoc("uTrans");
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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