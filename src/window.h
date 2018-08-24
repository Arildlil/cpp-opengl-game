#ifndef WINDOW_H
#define WINDOW_H

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include <string>
#include <iostream>

namespace Core {
    class Window {
    public:
        Window(int width, int height, std::string name);
        virtual ~Window();
        void show();
        GLFWwindow* get_window() const { return window; }
    private:
        int width;
        int height;
        std::string name;
        GLFWwindow *window;
    };
}

#endif