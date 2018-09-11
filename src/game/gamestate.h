#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace Game {
    class GameState {
        GameState();
        virtual ~GameState();
        virtual void handleInput() = 0;
        virtual void handleEvent() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
    };
};

#endif