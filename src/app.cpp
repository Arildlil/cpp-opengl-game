#include "core/gl_header.h"

#include "core/window.h"
#include "core/vertex.h"
#include "core/shader.h"
#include "core/camera.h"
#include "core/mesh.h"
#include "core/material.h"
#include "core/model.h"

#include "game/entity.h"
#include "game/gamestaterunning.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stack>



void cleanup() {
    glfwTerminate();
}

/*
void process_input(Core::Window& window, Core::Camera& camera, Game::GameState& state) {
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
}*/

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    glfwInit();

    Core::Window gameWindow {800, 600, "My First OpenGL Window"};

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: Failed to initialize GLAD!" << std::endl;
        cleanup();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    
    std::vector<Core::Vertex> verticesPyramid {
        {{0.0f, 0.5f, 0.0f}},     // top
        {{0.5f, -0.5f, 0.5f}},    // front right
        {{-0.5f, -0.5f, 0.5f}},   // front left
        {{-0.5f, -0.5f, -0.5f}},  // back left
        {{0.5f, -0.5f, -0.5f}},   // back right
    };

    std::vector<unsigned int> indicesPyramid {
        0, 1, 2,    // front triangle
        0, 2, 3,    // left triangle
        0, 1, 4,    // right triangle
        0, 3, 4,    // back triangle
        2, 3, 4,    // bot triangle left
        1, 2, 4,    // bot triangle right
    };

    std::vector<Core::Vertex> verticesBox {
        {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
        {{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
        {{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
        {{-0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 
        {{-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}}, 

        {{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}},

        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},

        {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}},
        {{0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}},

        {{-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}},

        {{-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}},
        {{0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}},
        {{-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}}
    };

    std::vector<unsigned int> emptyIndices {};
    std::vector<Core::Texture> emptyTextures {};


    // Setup objects
    Core::Shader objectShader {std::string{"src/shaders/current"}};
    Core::Shader lampShader {std::string{"src/shaders/current"}};

    Core::Camera camera {};

    /*
    Core::Mesh lamp {verticesBox, emptyIndices, emptyTextures};
    Core::Mesh mesh {verticesBox, emptyIndices, emptyTextures};
    */

    Core::Mesh mesh {verticesBox, emptyIndices, emptyTextures};
    Core::Mesh pyramid {verticesPyramid, indicesPyramid, emptyTextures};

    Core::Model simpleTower {"assets/simpleTower/simpleTower.obj", false};
    
    std::cout << "Loaded!\n";

    Core::Material materialMat {
        glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        32.0f
    };
    Core::Material lightMat {
        glm::vec3(0.2f, 0.2f, 0.2f) * glm::vec3(0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f) * glm::vec3(0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.0f
    };

    //std::stack<Game::GameState&> gameState {};
    Game::GameStateRunning gameStateRunning {gameWindow, camera};
    //gameState.push(gameStateRunning);


    gameWindow.show();

    glm::vec3 objectColor {glm::vec3(1.0f, 0.5f, 0.31f)};
    glm::vec3 lightColor {glm::vec3(1.0f, 1.0f, 1.0f)};
    glm::vec3 lampPos {glm::vec3(1.2f, 1.0f, 2.0f)};


    GLFWwindow* main_window {gameWindow.get_window()};
    while (!glfwWindowShouldClose(main_window)) {
        // input handling
        //process_input(gameWindow, camera, gameState.top());

        // rendering
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //gameState.top().handleInput();
        gameStateRunning.handleInput();
        //gameState.top().update(0.0f);
        gameStateRunning.update(0.0f);


        // change color
        glm::mat4 modelMatrix {};
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 0.0f, 0.0f));
        objectShader.setMat4("uModel", modelMatrix);
        
        objectShader.setVec3("material.ambient", materialMat.ambient());
        objectShader.setVec3("material.diffuse", materialMat.diffuse());
        objectShader.setVec3("material.specular", materialMat.specular());
        objectShader.setFloat("material.shininess", materialMat.shininess());
        objectShader.setVec3("light.ambient", lightMat.ambient());
        objectShader.setVec3("light.diffuse", lightMat.diffuse());
        objectShader.setVec3("light.specular", lightMat.specular());
        objectShader.setVec3("light.pos", lampPos);

        double curTime = glfwGetTime();
        double lampPosX = (sin(curTime) * 3.0f);
        double lampPosZ = (cos(curTime) * 3.0f);
        lampPos = glm::vec3(lampPosX, 0.5f, lampPosZ);

        objectShader.setVec3("uViewPos", camera.getViewPos());

        glm::mat4 viewMatrix, projMatrix;
        viewMatrix = camera.getViewMatrix();
        projMatrix = glm::perspective(glm::radians(45.0f), 
            (float)gameWindow.getWidth() / (float)gameWindow.getHeight(), 0.1f, 100.0f);
            
        objectShader.setMat4("uView", viewMatrix);
        objectShader.setMat4("uProj", projMatrix);

        mesh.draw(objectShader);
        
        glm::vec3 towerPos = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::mat4 simpleTowerModelMatrix {};
        simpleTowerModelMatrix = glm::translate(simpleTowerModelMatrix, towerPos);
        simpleTowerModelMatrix = glm::rotate(simpleTowerModelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        simpleTowerModelMatrix = glm::scale(simpleTowerModelMatrix, glm::vec3(0.2f));
        objectShader.setMat4("uModel", simpleTowerModelMatrix);

        simpleTower.draw(objectShader);
        
        


        // Prepare lamp shader
        /*
        glm::mat4 lampModelMatrix {};
        lampModelMatrix = glm::translate(lampModelMatrix, lampPos);
        lampModelMatrix = glm::scale(lampModelMatrix, glm::vec3(0.2f));
        lampShader.setMat4("uModel", lampModelMatrix);

        lampShader.setMat4("uView", viewMatrix);
        lampShader.setMat4("uProj", projMatrix);
        */
        glm::mat4 pyramidModelMatrix {};
        pyramidModelMatrix = glm::translate(pyramidModelMatrix, lampPos);
        pyramidModelMatrix = glm::scale(pyramidModelMatrix, glm::vec3(0.2f));
        objectShader.setMat4("uModel", pyramidModelMatrix);

        objectShader.setMat4("uView", viewMatrix);
        objectShader.setMat4("uProj", projMatrix);

        pyramid.draw(objectShader);
        //lamp.draw(objectShader);

        // check/call events and swap buffers
        glfwSwapBuffers(main_window);
        glfwPollEvents();
    }

    std::cout << "Closing app..." << std::endl;

    cleanup();

    return 0;
}