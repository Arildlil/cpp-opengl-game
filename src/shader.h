#ifndef SHADER_H
#define SHADER_H

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
        private:
            long m_shaderProgram;
    };
};

#endif