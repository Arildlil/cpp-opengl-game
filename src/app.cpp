#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include "window.h"

#include <iostream>
#include <string>

void cleanup() {
    glfwTerminate();
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
    
    GLFWwindow* main_window {game_window.get_window()};
    while (!glfwWindowShouldClose(main_window)) {
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }

    std::cout << "Closing app..." << std::endl;

    cleanup();

    return 0;
}