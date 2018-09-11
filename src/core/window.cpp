#include "window.h"

using namespace Core;

Window::Window(int width = 800, int height = 600, std::string name = {"Window"})
            :width{width}, height{height}, name{name}
{
    if (width < 0) width = 0;
    if (height < 0) height = 0;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    std::cout << "Constructor!" << std::endl;

    std::cout << "Setting current context!" << std::endl;
    glfwMakeContextCurrent(window);
}

void Window::show() {
    glViewport(0, 0, width, height);    // Location of render window and size of the render area 
}

Window::~Window() {
    std::cout << "Destroying window!" << std::endl;
    //glfwDestroyWindow(window);
}