#ifndef GAMESTATERUNNING_H
#define GAMESTATERUNNING_H

#include "gamestate.h"
#include "../core/window.h"
#include "../core/camera.h"
#include "../core/gl_header.h"

namespace Game {
    class GameStateRunning : public GameState {
        public:
            GameStateRunning(Core::Window& window, Core::Camera& camera);
            virtual ~GameStateRunning();
            void handleInput() override;
            void handleEvent() override;
            void update(float deltaTime) override;
            void render() override;
        private:
            Core::Window& m_window;
            Core::Camera& m_camera;
    };
};

#endif