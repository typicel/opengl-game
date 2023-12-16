//
// Created by tyler on 12/15/2023.
//

#include "glad/glad.h"
#include "Shader.h"

class DebugDraw {
public:
    DebugDraw();
    void DrawRectangle(float x, float y, float width, float height);
    void DrawLine(float pos, float len);

private:
    Shader debugShader;
};


