#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include "window.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

//static std::vector< std::vector<char> > shaders {};

std::vector<std::string>& load_shaders(const std::vector<const char*>& files, 
    std::vector<std::string>& output) 
{
    for (const char* file_name : files) {
        std::ifstream ifs {file_name};
        std::string temp (512, '\0');
        if (!ifs) {
            std::cerr << "Invalid file name: " << file_name << std::endl;
            continue;
        }
        
        std::cout << "Looking at file " << file_name << std::endl;
        char c;
        while (ifs.get(c)) {
            temp += c;
        }
        output.push_back(temp);
    }

    return output;
}

void cleanup() {
    glfwTerminate();
}

void process_input(Core::Window& window) {
    if (glfwGetKey(window.get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window.get_window(), true);
    }
}

void game_loop(Core::Window& game_window) {
    GLFWwindow* main_window {game_window.get_window()};
    while (!glfwWindowShouldClose(main_window)) {
        // input handling
        process_input(game_window);

        // rendering
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check/call events and swap buffers
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }
}

int main(int argc, char **argv) {
    
    glfwInit();
    
    Core::Window game_window {800, 600, "My First OpenGL Window"};

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: Failed to initialize GLAD!" << std::endl;
        //cleanup();
        //return -1;
    }


    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  // top left
    };

    unsigned int indices[] = {
        0, 1, 3,    // first triangle
        1, 2, 3,    // second triangle
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



    // Setup shaders
    const std::vector<const char*> shader_files {"src/minimal.vert", "src/minimal.frag"};
    std::vector<std::string> shader_contents {};
    load_shaders(shader_files, shader_contents);
    for (std::string shader : shader_contents) {
        std::cout << shader << std::endl;
    }

    game_window.show();
    game_loop(game_window);

    std::cout << "Closing app..." << std::endl;

    cleanup();

    return 0;
}