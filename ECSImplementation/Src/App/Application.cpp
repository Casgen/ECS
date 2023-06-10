#include "Application.h"

#include "../Components/ColorComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/TransformComponent.h"
#include "Core/Buffers/Public/VertexBufferLayout.h"
#include "Core/Models/Public/Program.h"
#include "Utils/Utils.h"
#include <filesystem>

#include <glm/vec3.hpp>


int Application::Run()
{
    InitObjects();
    Loop();
    return 0;
}

void Application::InitObjects()
{
    std::string path = std::filesystem::current_path().append("../../Res/testShaders/testShaders").string();
    m_Program = new Program(path);
    m_ECS = new ECS(3, sizeof(MeshComponent), sizeof(TransformComponent), sizeof(ColorComponent));
    Entity entity = m_ECS->CreateEntity();
    m_Entities = std::vector<Entity>(1);

    TransformComponent transformComponent = TransformComponent{glm::vec2(0.5, -0.5)};
    ColorComponent colorComponent = ColorComponent{glm::vec3(1.f, 0.5, 2.f)};

    m_Vao = new VertexArray();
    m_Vao->Bind();

    float* vertexData = new float[15]{
        -0.5, -0.5, 1.f, 0.f, 0.f,
        0.0f, 0.5, 0.f, 1.f, 0.f,
        0.5, -0.5, 0.f, 0.f, 1.f
    };

    VertexBuffer* vb = new VertexBuffer(vertexData, sizeof(float) * 15);

    VertexBufferLayout layout = VertexBufferLayout();
    layout.push<float>(2);
    layout.push<float>(3);

    m_Vao->addBuffer(*vb, layout);

    // MeshComponent meshComponent = {vb, *m_Vao};
    //
    // m_ECS->AddComponent(entity.id, 0, &meshComponent);
    // m_ECS->AddComponent(entity.id, 1, &transformComponent);
    // m_ECS->AddComponent(entity.id, 2, &colorComponent);
}

void Application::OnEvent(Event& Event)
{
    
}


void Application::Loop()
{
    QueryResult* result = m_ECS->Query(3, 0, 1 ,2);

    while (!m_Window->ShouldClose())
    {
        
        for (uint32_t id : result->queriedEntities) {
          MeshComponent* mesh = m_ECS->GetComponentCast<MeshComponent>(id, 0);
          m_Renderer->DrawArrays(mesh->vertexArray,*m_Program,GL_TRIANGLES,0,3);
        }

        m_Renderer->DrawArrays(*m_Vao,*m_Program,GL_TRIANGLES,0,3);

        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }

    delete m_Program;
    
}

