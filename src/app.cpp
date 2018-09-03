#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include "window.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>



std::vector<std::string>& load_shader_files(const std::vector<const char*>& files, 
    std::vector<std::string>& output) 
{
    for (const char* file_name : files) {
        std::ifstream ifs {file_name};
        std::string temp {};
        if (!ifs) {
            std::cerr << "Invalid file name: " << file_name << std::endl;
            continue;
        }
        
        std::cout << "Looking at file " << file_name << std::endl;
        char c;
        while (ifs.get(c)) {
            temp += c;
        }
        temp += '\0';
        output.push_back(temp);
    }

    return output;
}

bool compile_shader(GLuint shader_id, const std::string& shader_data) {
    int success {0};
    constexpr int max_info_len {512};
    char info_log[max_info_len];

    const GLchar* cdata {shader_data.c_str()};
    glShaderSource(shader_id, 1, &cdata, NULL);
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, max_info_len, NULL, info_log);
        std::cerr << "Shader " << shader_id << ": " << info_log << std::endl;
        glDeleteShader(shader_id);
        return false;
    }

    return true;
}

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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Setup shaders
    const std::vector<const char*> shader_files {"src/minimal.vert", "src/minimal.frag"};
    std::vector<std::string> shader_contents {};
    load_shader_files(shader_files, shader_contents);

    // Compiler shaders
    std::vector<GLuint> shaders {glCreateShader(GL_VERTEX_SHADER), glCreateShader(GL_FRAGMENT_SHADER)};
    for (int i {0}; i < shaders.size() && i < shader_files.size(); i++) {
        if (!compile_shader(shaders[i], shader_contents[i])) {
            cleanup();
            return -1;   
        }
    }

    // Create and link shader program
    GLuint shader_program {glCreateProgram()};
    for (GLuint shader_id : shaders) {
        glAttachShader(shader_program, shader_id);
    }
    
    int success {0};
    constexpr int max_info_len {512};
    char info_log[max_info_len];
    
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, max_info_len, NULL, info_log);
        std::cerr << "Shader linking: " << info_log << std::endl;
        cleanup();
        return -1;
    }

    for (GLuint shader_id : shaders) {
        glDeleteShader(shader_id);
    }

    game_window.show();

    GLFWwindow* main_window {game_window.get_window()};
    while (!glfwWindowShouldClose(main_window)) {
        // input handling
        process_input(game_window);

        // rendering
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
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