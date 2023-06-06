#pragma once
#include <functional>
#include <GLFW/glfw3.h>

#include "../../Event/Public/Event.h"
#include "../../Models/Public/MouseState.h"
#include <imGui/imgui.h>

class Window
{
public:
    struct WindowProps
    {
        std::string m_Title;
        unsigned int m_Width, m_Height;
        std::function<void(Event&)> m_CbFunction;
        ImGuiIO* m_ImGuiIO;

        WindowProps(const std::string& title = "Hello, World", unsigned int width = 1280, unsigned int height = 720)
            : m_Title(title), m_Width(width), m_Height(height) {}
    };
    
    Window(const WindowProps& props = WindowProps());

    ~Window()
    {
        glfwTerminate();
        glfwDestroyWindow(m_GlfwWindow);
    }

    [[nodiscard]] GLFWwindow* GetGLFWWindow() const {return m_GlfwWindow;}

    void SetEventCallback(const std::function<void(Event&)>& callback)
    {
        m_Props.m_CbFunction = callback;
    }

    [[nodiscard]] MouseState& GetMouseState()
    {
        return m_MouseState;
    }

    [[nodiscard]] WindowProps GetProps() const
    {
        return m_Props;
    }

    void SetWindowSize(const int& width, const int& height)
    {
        m_Props.m_Width = width;
        m_Props.m_Height = height;
        glfwSetWindowSize(m_GlfwWindow, width, height);
    }

    int ShouldClose() const
    {
        return glfwWindowShouldClose(m_GlfwWindow);
    }

    void PollEvents() const
    {
        glfwPollEvents();
    }

    void SwapBuffers() const
    {
        glfwSwapBuffers(m_GlfwWindow);
    }

private:
    GLFWwindow* m_GlfwWindow;
    WindowProps m_Props;

    MouseState m_MouseState;
};
