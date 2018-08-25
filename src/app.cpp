#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include "window.h"

#include <iostream>
#include <string>

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

    game_window.show();

    game_loop(game_window);

    std::cout << "Closing app..." << std::endl;

    cleanup();

    return 0;
}