//
// Created by tyler on 12/11/2023.
//

#ifndef RENDERER_RESOURCEMANAGER_H
#define RENDERER_RESOURCEMANAGER_H

#include <map>
#include <string>
#include <glad/glad.h>
#include "stb_image.h"
#include "Shader.h"
#include "Texture2D.h"

class ResourceManager {
public:
    static Shader GetShader(const std::string& name);
    static Texture2D GetTexture(const std::string& name);

    static Shader LoadShader(const char* vShaderPath, const char* fShaderPath, std::string name);
    static Texture2D LoadTexture(const char* texturePath, std::string name, bool alpha);
private:
    ResourceManager() {};
    static std::map<std::string, Shader> m_Shaders;
    static std::map<std::string, Texture2D> m_Textures;

    static Shader loadShaderFromPath(const char* vShaderPath, const char* fShaderPath);
    static Texture2D loadTextureFromPath(const char* texturePath, bool alpha);
};


#endif //RENDERER_RESOURCEMANAGER_H
