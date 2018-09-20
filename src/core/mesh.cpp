#include "mesh.h"
#include "gl_header.h"

#include <iostream>

using namespace Core;

Mesh::Mesh(std::vector<Core::Vertex> vertices, std::vector<unsigned int> indices,
    std::vector<Core::Texture> textures) 
    :m_vertices{vertices}, m_indices{indices}, m_textures{textures}
{
    setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Core::Vertex),
        &m_vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
        &m_indices[0], GL_STATIC_DRAW);

    // positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex), 
        (void*)offsetof(Core::Vertex, m_pos));
    // normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex), 
        (void*)offsetof(Core::Vertex, m_normal));
    // texture coords
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex), 
        (void*)offsetof(Core::Vertex, m_texCoords));
    // tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex), 
        (void*)offsetof(Core::Vertex, m_tangent));
    // bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex), 
        (void*)offsetof(Core::Vertex, m_bitangent));
    

    glBindVertexArray(0);
}

void Mesh::bind() {
    glBindVertexArray(m_VAO);
}

void Mesh::unbind() {
    glBindVertexArray(0);
}

void Mesh::draw(Core::Shader& shader) {
    unsigned int diffuseNr {1};
    unsigned int specularNr {1};
    unsigned int normalNr {1};
    unsigned int heightNr {1};
    
    for (unsigned int i {0}; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name {m_textures[i].type};
        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if (name == "texture_specular") {
            number = std::to_string(specularNr++);
        } else if (name == "texture_normal") {
            number = std::to_string(normalNr++);
        } else if (name == "texture_height") {
            number = std::to_string(heightNr++);
        }

        std::string shaderLocName {name + number};
        glUniform1i(shader.getTransformLoc(shaderLocName), i);
        //shader.setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // Draw mesh
    shader.bind();
    bind();
    if (m_indices.size() == 0) { 
        glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    } else {
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (void*)0);
    }
    unbind();
    glActiveTexture(GL_TEXTURE0);
}