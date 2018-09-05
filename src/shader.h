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
        private:
            long m_shaderProgram;
    };
};

#endif