#include "model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace Core;

unsigned int textureFromFile(const char *path, const std::string& directory, bool gamme);


Model::Model(const std::string& path, bool gamma) 
    :m_gammaCorrection{gamma}
{
    loadModel(path);

    std::cout << "num meshes: " << m_meshes.size() << std::endl;
    std::cout << m_meshes[0].m_vertices.size() << ", " << m_meshes[0].m_indices.size() << std::endl;
    std::cout << "path: " << path << std::endl;
}

Model::Model(const std::vector<Core::Mesh>& meshes, bool gamma) 
    :m_gammaCorrection{gamma}
{
    for (int i {0}; i < meshes.size(); i++) {
        m_meshes.push_back(Core::Mesh(meshes[i].m_vertices,
            meshes[i].m_indices, meshes[i].m_textures));
    }
}

void Model::draw(Core::Shader& shader) {
    for (unsigned int i {0}; i < m_meshes.size(); i++) {
        m_meshes[i].draw(shader);

        /*
        std::cout << m_meshes[i].m_vertices.size() << ", " << m_meshes[i].m_indices.size() << std::endl;
        std::cout << "directory: " << m_directory << std::endl;
        */
    }
}

void Model::loadModel(const std::string& path) 
{
    Assimp::Importer importer;
    // Read the file
    const aiScene *scene {importer.ReadFile(path, 
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace)};
        // | aiProcess_GenSmoothNormals

    std::cout << "Read file \'" << path << "\'" << std::endl;
    
    // Error checking
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    // Get the directory part of the path
    m_directory = path.substr(0, path.find_last_of('/'));

    // Process teh ASSIMP nodes recursively
    processNode(scene->mRootNode, scene);

    std::cout << "Model loaded! Directory: " << m_directory << std::endl;
    std::cout << "Complete path: " << path << std::endl;
}

/* 
 * Processes the nodes recursively, along with its children. 
 */
void Model::processNode(aiNode *node, const aiScene *scene) 
{
    std::cout << "\tProcessing node...\n";
    std::cout << "\tNumMeshes: " << node->mNumMeshes << std::endl;
    std::cout << "\tNumChildren: " << node->mNumChildren << std::endl;

    // Process all meshes in a node
    for (unsigned int i {0}; i < node->mNumMeshes; i++) {
        // The node contains the indices and relations between nodes,
        // while the scene contains the data.
        aiMesh *mesh {scene->mMeshes[node->mMeshes[i]]};
        m_meshes.push_back(processMesh(mesh, scene));
    }

    std::cout << "Processes meshes, now processing children nodes...\n";

    // Process the children after
    for (unsigned int i {0}; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) 
{
    std::vector<Core::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Core::Texture> textures;

    std::cout << "\t\tProcessing mesh! NumVertices: " << mesh->mNumVertices << "\n";

    // Walk through all vertices
    for (unsigned int i {0}; i < mesh->mNumVertices; i++) {
        Core::Vertex vertex;
        // placeholder vector for easier handling than using assimps own vector
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.m_pos = vector;

        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.m_normal = vector;
        
        // texture coordinates
        if (mesh->mTextureCoords[0]) {  // does the mesh have textures?
            glm::vec2 vec;
            // we assume that the models where a vertex can have multiple texture coords
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.m_texCoords = vec;
        } else {
            vertex.m_texCoords = glm::vec2(0.0f, 0.0f);
        }

        /*
        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.m_tangent = vector;

        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.m_bitangent = vector;
        */
        
        vertices.push_back(vertex);
    }

    std::cout << "\t\tProcessing faces! NumFaces: " << mesh->mNumFaces << "\n";

    // walk through each of the mesh faces and get the indices of it
    for (unsigned int i {0}; i < mesh->mNumFaces; i++) {
        aiFace face {mesh->mFaces[i]};
        for (unsigned int j {0}; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    std::cout << "\t\tProcessing materials!" << "\n";

    // process materials
    aiMaterial *material {scene->mMaterials[mesh->mMaterialIndex]};

    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Core::Texture> diffuseMaps {loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse")};
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // 2. specular maps
    std::vector<Core::Texture> specularMaps {loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular")};
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // 3. normal maps
    std::vector<Core::Texture> normalMaps {loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal")};
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // 4. height maps
    std::vector<Core::Texture> heightMaps {loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height")};
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    std::cout << "\t\ttextures.size(): " << textures.size() << std::endl;

    // return a mesh object from the extraced mesh data
    return Core::Mesh(vertices, indices, textures);
}

/* 
 * Checks the material textures of a given type and loads them if 
 * not done already.
 */
std::vector<Core::Texture> Model::loadMaterialTextures(aiMaterial *mat, 
                aiTextureType type, std::string typeName) 
{    
    std::vector<Core::Texture> textures;
    for (unsigned int i {0}; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        // Only load texture if it hasn't been loaded already.
        bool skip {true};
        for (unsigned int j {0}; j < m_texturesLoaded.size(); j++) {
            if (std::strcmp(m_texturesLoaded[j].path.c_str(), str.C_Str()) == 0) {
                // The textures was already loaded, continue
                textures.push_back(m_texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture;
            texture.id = textureFromFile(str.C_Str(), m_directory, m_gammaCorrection);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int textureFromFile(const char *path, const std::string& directory, bool gamma) 
{
    std::string fileName {directory + '/' + std::string(path)};

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        stbi_image_free(data);

    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}