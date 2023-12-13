#pragma once

#include "GLFW/glfw3.h"

// std
#include <map>
#include <vector>

class InputManager {
public:
    explicit InputManager(const std::vector<int>& keysToMonitor);
    ~InputManager();
    bool getIsKeyDown(int key);

public:
    static void setupKeyInputs(GLFWwindow* window);

private:
    void setIsKeyDown(int key, bool isDown);
    std::map<int, bool> m_keys;
    bool m_isEnabled;

private:
    static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static std::vector<InputManager*> _instances;
};
