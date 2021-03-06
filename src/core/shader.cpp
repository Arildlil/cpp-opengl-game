#include "shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace Core;

static GLuint createShader(const std::string& shaderCode, GLenum shaderType);
static std::string readFromDisk(const std::string& fileName);
static bool verifyShader(GLuint shaderId);

Shader::Shader(const std::string& shaderName)
    :m_shaderProgram{0} 
{
    int success {0};
    constexpr int max_info_len {512};
    char info_log[max_info_len];
    std::vector<GLuint> shaders {};
    
    GLuint vertexShader = createShader(readFromDisk(shaderName + ".vert"), GL_VERTEX_SHADER);
    GLuint fragmentShader = createShader(readFromDisk(shaderName + ".frag"), GL_FRAGMENT_SHADER);

    if (verifyShader(vertexShader)) shaders.push_back(vertexShader);
    if (verifyShader(fragmentShader)) shaders.push_back(fragmentShader);

    // Create and link shader program
    m_shaderProgram = {glCreateProgram()};
    for (GLuint shader : shaders) {
        glAttachShader(m_shaderProgram, shader);
    }
    
    glLinkProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shaderProgram, max_info_len, NULL, info_log);
        std::cerr << "Shader linking: " << info_log << std::endl;
    }

    for (GLuint shader : shaders) {
        glDeleteShader(shader);
    }
}

Shader::~Shader() {
    glDeleteProgram(m_shaderProgram);
}

bool Shader::operator==(const Shader& other) {
    return (m_shaderProgram == other.getProgram());
}

bool Shader::operator!=(const Shader& other) {
    return !(m_shaderProgram == other.getProgram());
}

void Shader::bind() {
    glUseProgram(m_shaderProgram);
}

void Shader::setWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Shader::setSolidMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

long Shader::getProgram() const {
    return m_shaderProgram;
}

unsigned int Shader::getTransformLoc(const std::string& transform) {
    return glGetUniformLocation(m_shaderProgram, transform.c_str());
}

void Shader::setFloat(const std::string& trans, float flt) {
    unsigned int transLoc {getTransformLoc(trans)};
    glUniform1f(transLoc, flt);
}

void Shader::setVec3(const std::string& trans, glm::vec3 vec) {
    unsigned int transLoc {getTransformLoc(trans)};
    glUniform3f(transLoc, vec.x, vec.y, vec.z);
}

void Shader::setVec4(const std::string& trans, glm::vec4 vec) {
    unsigned int transLoc {getTransformLoc(trans)};
    glUniform4f(transLoc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMat4(const std::string& trans, glm::mat4 mat) {
    unsigned int transLoc = getTransformLoc(trans);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

static GLuint createShader(const std::string& shaderCode, GLenum shaderType) {
    int success {0};
    constexpr int max_info_len {512};
    char info_log[max_info_len];

    //static_assert(shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER);
    GLuint shader {glCreateShader(shaderType)};
    const GLchar* cdata {shaderCode.c_str()};
    glShaderSource(shader, 1, &cdata, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, max_info_len, NULL, info_log);
        std::cerr << "Shader " << shader << ": " << info_log << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static std::string readFromDisk(const std::string& fileName) {
    std::ifstream ifs {fileName.c_str()};
    std::string data {};

    if (!ifs) {
        std::cerr << "Invalid file name: " << fileName << std::endl;
        return "";
    }

    char c;
    while (ifs.get(c)) {
        data += c;
    }
    data += '\0';

    ifs.close();

    return data;
}

static bool verifyShader(GLuint shader) {
    if (shader == 0) {
        return false;
    }

    return true;
}
