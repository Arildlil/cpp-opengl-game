#ifndef SHADER_H
#define SHADER_H

#include <../include/glm/glm.hpp>

#include <vector>
#include <string>

namespace Core {
    class Shader {
        public:
            Shader(const std::string& fileName);
            virtual ~Shader();
            void bind();
            void setWireframeMode();
            void setSolidMode();
            long getProgram();
            unsigned int getTransformLoc(const std::string& transform);
            void setVec4(const std::string& trans, glm::vec4 vec);
            void setMat4(const std::string& trans, glm::mat4 mat);
        private:
            long m_shaderProgram;
    };
};

#endif