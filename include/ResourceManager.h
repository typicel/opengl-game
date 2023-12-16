#pragma once

#include <map>
#include <string>
#include <glad/glad.h>

#include "stb_image.h"
#include "Shader.h"
#include "Texture2D.h"
#include <filesystem>

class ResourceManager {
public:
    static Shader GetShader(const std::string& name);
    static Texture2D GetTexture(const std::string& name);

    static Shader LoadShader(const std::string& vShaderPath, const std::string& fShaderPath, std::string name);
    static Texture2D LoadTexture(const std::string& texturePath, std::string name, bool alpha);
private:
    ResourceManager() {};
    static std::map<std::string, Shader> m_Shaders;
    static std::map<std::string, Texture2D> m_Textures;

    static Shader loadShaderFromPath(const std::string& vShaderPath, const std::string& fShaderPath);
    static Texture2D loadTextureFromPath(const std::string& texturePath, bool alpha);
};

