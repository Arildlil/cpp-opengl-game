#ifndef MESH_H
#define MESH_H

#include "gl_header.h"

#include "vertex.h"
#include "shader.h"
#include "texture.h"

#include <vector>

namespace Core {
    class Mesh {
        public:
            Mesh(std::vector<Core::Vertex>& vertices, std::vector<unsigned int>& indices,
                std::vector<Core::Texture>& textures);
            virtual ~Mesh();
            void bind();
            void unbind();
            void draw(Core::Shader& shader);

            std::vector<Core::Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<Core::Texture> m_textures;
        private:
            void setupMesh();

            GLuint m_VBO, m_VAO, m_EBO;
    };
};

#endif