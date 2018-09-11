#include "mesh.h"

#include <iostream>

using namespace Core;

Mesh::Mesh(std::vector<Core::Vertex>& vertices, std::vector<unsigned int>& indices) 
    :m_VBO{0}, m_VAO{0}, m_EBO{0}, m_vertices{vertices}, m_indices{indices}
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    std::cout << m_vertices.size() << std::endl;
    std::cout << m_indices.size() << std::endl;

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), &m_vertices[0], GL_STATIC_DRAW);
    /*
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), &m_indices[0], GL_STATIC_DRAW);
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // for normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    //glDeleteBuffers(1, &m_EBO);
}

void Mesh::bind() {
    glBindVertexArray(m_VAO);
}

void Mesh::unbind() {
    glBindVertexArray(0);
}

void Mesh::draw() const {
    //glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}