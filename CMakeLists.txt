cmake_minimum_required(VERSION 3.26)
project(renderer)

set(CMAKE_CXX_STANDARD 17)

add_executable(renderer main.cpp
        include/VertexBuffer.h
        IndexBuffer.cpp
        include/IndexBuffer.h
        VertexBuffer.cpp
        Shader.cpp
        include/Shader.h
        SpriteRenderer.cpp
        include/SpriteRenderer.h
        Texture2D.cpp
        include/Texture2D.h
        include/stb_image.h
        include/Errors.h
        ResourceManager.cpp
        include/ResourceManager.h
        include/ResourceManager.h
        ResourceManager.cpp
        Entity.cpp
        include/Entity.h
        Game.cpp
        include/Game.h
        InputManager.cpp
        include/InputManager.h)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

target_link_libraries(renderer PRIVATE glad::glad)
target_link_libraries(renderer PRIVATE glfw)
target_link_libraries(renderer PRIVATE glm::glm)
target_link_libraries(renderer PRIVATE box2d::box2d)
