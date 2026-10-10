#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class OpenGLContextGLFW {
private:
    GLFWwindow* m_pWindow = nullptr;

public:
    inline GLFWwindow* getWindow() {
        return m_pWindow;
    }

    void open() {
        // Init GLFW
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        // Create GLFW Window
        m_pWindow = glfwCreateWindow(800, 800, "Test Window", nullptr, nullptr);
        if (m_pWindow == nullptr) {
            throw std::runtime_error("Failed to create GLFW window");
        }

        // Use context
        glfwMakeContextCurrent(m_pWindow);
        
        // Init GLAD
        if (!gladLoadGL(glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

    void terminate() {
        if (m_pWindow != nullptr) {
            glfwDestroyWindow(m_pWindow);
            m_pWindow = nullptr;
        }
        glfwTerminate();
    }
};
