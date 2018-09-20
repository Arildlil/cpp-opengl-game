#ifndef MODEL_H
#define MODEL_H

#include "shader.h"
#include "mesh.h"
#include "texture.h"

#include "../../include/assimp/Importer.hpp"
#include "../../include/assimp/scene.h"
#include "../../include/assimp/postprocess.h"

#include <string>


/* 
 * This class and its methods are taken from the 'learnopengl.com' tutorials. 
 */
namespace Core {
    class Model {
        public:
            Model(const std::string& path, bool gamma = false);
            void draw(Core::Shader& shader);
        private:
            void loadModel(const std::string& path);
            void processNode(aiNode *node, const aiScene *scene);
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            std::vector<Core::Texture> loadMaterialTextures(aiMaterial *mat, 
                aiTextureType type, std::string typeName);

            std::vector<Core::Texture> m_texturesLoaded;
            std::vector<Core::Mesh> m_meshes;
            std::string m_directory;
            bool m_gammaCorrection;
    };
};

#endif