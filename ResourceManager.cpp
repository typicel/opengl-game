#include "include/ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::map<std::string, Shader> ResourceManager::m_Shaders;
std::map<std::string, Texture2D> ResourceManager::m_Textures;

Shader ResourceManager::GetShader(const std::string& name) {
    return m_Shaders[name];
}

Texture2D ResourceManager::GetTexture(const std::string& name) {
    return m_Textures[name];
}

Shader ResourceManager::LoadShader(const std::string& vShaderPath, const std::string& fShaderPath, std::string name) {
    Shader shader = loadShaderFromPath(vShaderPath, fShaderPath);
    m_Shaders[name] = shader;
    return shader;
}

Texture2D ResourceManager::LoadTexture(const std::string& texturePath, std::string name, bool alpha) {
    Texture2D texture = loadTextureFromPath(texturePath, alpha);
    m_Textures[name] = texture;
    return texture;
}

Texture2D ResourceManager::loadTextureFromPath(const std::string& texturePath, bool alpha)
{
    Texture2D texture;
    if(alpha)
    {
        texture.InternalFormat = GL_RGBA;
        texture.ImageFormat = GL_RGBA;
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    texture.Generate(width, height, data);

    stbi_image_free(data);
    std::cout << "Texture2D | Loaded texture " << texturePath << std::endl;
    return texture;
}

Shader ResourceManager::loadShaderFromPath(const std::string& vShaderPath, const std::string& fShaderPath) {

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertShaderFile("C:/Users/tyler/Projects/renderer/Assets/Shaders/" + vShaderPath);
    std::ifstream fragShaderFile("C:/Users/tyler/Projects/renderer/Assets/Shaders/" + fShaderPath);


    vertShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::stringstream vStream, fStream;

        vStream << vertShaderFile.rdbuf();
        fStream << fragShaderFile.rdbuf();

        vertShaderFile.close();
        fragShaderFile.close();

        vertexCode = vStream.str();
        fragmentCode = fStream.str();
    } catch (std::exception e)
    {
        std::cout << "Shader | Could not read one or more files" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    return Shader(vShaderCode, fShaderCode);
}


