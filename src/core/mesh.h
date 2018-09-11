#ifndef MESH_H
#define MESH_H

#include "gl_header.h"

#include "vertex.h"
#include "shader.h"

#include <vector>

namespace Core {
    class Mesh {
        public:
            Mesh(std::vector<Core::Vertex>& vertices, std::vector<unsigned int>& indices);
            virtual ~Mesh();
            void bind();
            void unbind();
            void draw() const;
        private:
            GLuint m_VBO, m_VAO, m_EBO;
            std::vector<Core::Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
    };
};

#endif