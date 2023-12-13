//
// Created by tyler on 12/13/2023.
//

#include "include/InputManager.h"

std::vector<InputManager*> InputManager::_instances;

InputManager::InputManager(const std::vector<int>& keysToMonitor) : m_isEnabled(true) {
    for(int key: keysToMonitor) {
        m_keys[key] = false;
    }

    InputManager::_instances.push_back(this);
}

InputManager::~InputManager() {
    _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}

bool InputManager::getIsKeyDown(int key) {
    bool result = false;
    auto it = m_keys.find(key);
    if(it != m_keys.end())
        result = m_keys[key];

    return result;
}

void InputManager::setIsKeyDown(int key, bool isDown) {
    auto it = m_keys.find(key);
    if(it != m_keys.end())
        m_keys[key] = isDown;
}

void InputManager::setupKeyInputs(GLFWwindow *window) {
    glfwSetKeyCallback(window, InputManager::callback);
}

void InputManager::callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    for(auto instance: _instances) {
        instance->setIsKeyDown(key, action != GLFW_RELEASE);
    }
}
