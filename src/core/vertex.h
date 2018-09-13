#ifndef VERTEX_H
#define VERTEX_H

#include <../../include/glm/glm.hpp>

namespace Core {
    struct Vertex {
        glm::vec3 m_pos;
        glm::vec3 m_normal;
        //glm::vec2 m_texCoords;

        Vertex(glm::vec3 pos, glm::vec3 normal/*, glm::vec2 coords = glm::vec2{0,0}*/) 
            :m_pos{pos}, m_normal{normal}/*, m_texCoords{coords}*/ {};
    };
};

#endif