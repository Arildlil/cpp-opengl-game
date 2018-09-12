#ifndef SHADER_H
#define SHADER_H

#include "gl_header.h"

#include <vector>
#include <string>

namespace Core {
    class Shader {
        public:
            Shader(const std::string& fileName);
            virtual ~Shader();
            bool operator==(const Shader& other);
            bool operator!=(const Shader& other);
            void bind();
            void setWireframeMode();
            void setSolidMode();
            long getProgram() const;
            unsigned int getTransformLoc(const std::string& transform);
            void setFloat(const std::string& trans, float flt);
            void setVec3(const std::string& trans, glm::vec3 vec);
            void setVec4(const std::string& trans, glm::vec4 vec);
            void setMat4(const std::string& trans, glm::mat4 mat);
        private:
            long m_shaderProgram;
    };
};

#endif