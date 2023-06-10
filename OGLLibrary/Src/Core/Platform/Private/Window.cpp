#pragma once

#include <glad/glad.h>
#include <iostream>

#include "../Public/Window.h"
#include "../../Event/Public/KeyEvent.h"
#include "../../Event/Public/MouseEvent.h"
#include "../../Event/Public/WindowEvent.h"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

Window::Window(const WindowProps& props)
    : m_Props(props)
{
    if (!glfwInit())
        throw std::runtime_error("Couldn't initialize GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_GlfwWindow = glfwCreateWindow(props.m_Width, props.m_Height, props.m_Title.c_str(), NULL, NULL);
    if (!m_GlfwWindow)
    {
        glfwTerminate();
        throw std::runtime_error("Couldn't create a GLFW window!");
    }
    
    glfwMakeContextCurrent(m_GlfwWindow);


    /*
     *   With this profile, The vertex array object (VAO) is not automatically created and bound when glEnableVertexAttribArray
     *   is called, thus resulting in an error. We need to therefore create and Bind a VAO ourselves.
     */


    glfwSwapInterval(1); // Turns on/off V-Sync
    glfwSetWindowUserPointer(m_GlfwWindow, this);

    if (gladLoadGL() == 0)
        throw std::runtime_error("GLAD Couldn't be initialized");

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        std::cout << "Debug Context initialized." << std::endl;
    }

    


    glfwSetKeyCallback(m_GlfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
    {
        const WindowProps& data = static_cast<Window*>(glfwGetWindowUserPointer(window))->m_Props;

        switch (action)
        {
        case GLFW_PRESS:
            {
                KeyPressedEvent event = KeyPressedEvent(key);
                return data.m_CbFunction(event);
            }
        case GLFW_RELEASE:
            {
                KeyReleasedEvent event = KeyReleasedEvent(key);
                return data.m_CbFunction(event);
            }
        case GLFW_REPEAT:
            {
                KeyRepeatedEvent event = KeyRepeatedEvent(key);
                return data.m_CbFunction(event);
            }
        }
    });

    glfwSetMouseButtonCallback(m_GlfwWindow, [](GLFWwindow* window, int button, int action, int mods) -> void
    {
        Window* usrWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
        case GLFW_PRESS:
            {
                MouseButtonPressedEvent event = MouseButtonPressedEvent(button);
                return usrWindow->m_Props.m_CbFunction(event);
            }
        case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event = MouseButtonReleasedEvent(button);
                return usrWindow->m_Props.m_CbFunction(event);
            }
        case GLFW_REPEAT:
            {
                MouseButtonRepeatedEvent event = MouseButtonRepeatedEvent(button);
                return usrWindow->m_Props.m_CbFunction(event);
            }
        }
    });

    glfwSetWindowCloseCallback(m_GlfwWindow, [](GLFWwindow* window) -> void
    {
        const WindowProps& data = static_cast<Window*>(glfwGetWindowUserPointer(window))->m_Props;

        WindowClosedEvent event;
        data.m_CbFunction(event);
    });

    glfwSetScrollCallback(m_GlfwWindow, [](GLFWwindow* window, double xoffset, double yoffset) -> void
    {
        const WindowProps& data = static_cast<Window*>(glfwGetWindowUserPointer(window))->m_Props;

        MouseScrolledEvent event(xoffset, yoffset);
        data.m_CbFunction(event);
    });

    glfwSetCursorPosCallback(m_GlfwWindow, [](GLFWwindow* window, double xpos, double ypos) -> void
    {
        const Window* usrWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

        MouseMovedEvent event(xpos, ypos);
        usrWindow->m_Props.m_CbFunction(event);
    });

    glfwSetWindowSizeCallback(m_GlfwWindow, [](GLFWwindow* window, int width, int height)
    {
        const Window* usrWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

        WindowResizedEvent event(width, height);
        usrWindow->m_Props.m_CbFunction(event);
    });

    //ImGUI initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    m_Props.m_ImGuiIO = &ImGui::GetIO();
    m_Props.m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    m_Props.m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    m_Props.m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows;
    m_Props.m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos; // Enable setting mouse position.

    ImGuiStyle& style = ImGui::GetStyle();
    if (m_Props.m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(m_GlfwWindow, false);
    ImGui_ImplOpenGL3_Init("#version 450");

}
