#pragma once
#include <memory>

#include <glad/glad.h>

#include "Core/Buffers/Public/VertexArray.h"
#include "Core/Renderer/Public/Renderer.h"
#include "Core/Platform/Public/Window.h"
#include "../ECS/ECS.h"

class Application
{
public:

    Application(unsigned int width, unsigned int height) : m_Renderer(std::make_unique<Renderer>())
    {
        Window::WindowProps windowProps = Window::WindowProps("ECS, Here we go", width, height);
        m_Window = std::make_unique<Window>(windowProps);
        m_Window->SetEventCallback(std::bind(&Application::OnEvent,this, std::placeholders::_1));
    }

    int Run();
    void InitObjects();
    void OnEvent(Event& event);
    void Loop();

private:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;

    std::vector<Entity> m_Entities;

    Program* m_Program;
    ECS* m_ECS;
    VertexArray* m_Vao;
};
