#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "../Public/Camera.h"

#include <complex>
#include <iostream>
#include <glm/ext/matrix_projection.hpp>

Camera::Camera(const glm::vec3& position, const float& aspectRatio, const glm::ivec2& resolution, const float& a, const float& z)
{
    m_ProjectionMat = glm::perspective(45.0f, aspectRatio, 0.001f, 50.f);
    m_AspRatio = aspectRatio;
    m_zNear = 0.1f;
    m_zFar = 50.f;
    m_MovementSpeed = 0.01f;
    m_MovementSpeedMax = 0.75f;
    m_MovementSpeedMin = 1e-3f;
    m_EyePos = position;
    m_UpVec = glm::vec3(0.0f, 1.0f, .0f);
    m_CurrentMovingDir = glm::vec3(0.0f);
    m_ViewPort = glm::ivec4(0,0,resolution);
    
    m_Azimuth = glm::clamp(a, 0.f, glm::pi<float>() * 2);
    m_Zenith = glm::clamp(z, -glm::pi<float>(), glm::pi<float>());

    CalculateAndSetVectors();
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
    m_MovingBF = new MovingBitField();
}

Camera::~Camera()
{
    delete m_MovingBF;
}

void Camera::SwitchProjection()
{
    if (m_IsPerspective)
    {
        if (m_AspRatio > 1.f)
            m_ProjectionMat = glm::ortho(-1.f / m_Zoom, 1.f / m_Zoom, (-1 / m_AspRatio) / m_Zoom,
                                       (1 / m_AspRatio) / m_Zoom, 0.001f, 100.f);
        else if (m_AspRatio < 1.f)
            m_ProjectionMat = glm::ortho((-1 / m_AspRatio) / m_Zoom, (1 / m_AspRatio) / m_Zoom, -1.f / m_Zoom,
                                       1.f / m_Zoom, 0.001f, 100.f);
        else
            m_ProjectionMat = glm::ortho(-1.f / m_Zoom, 1.f / m_Zoom, -1.f / m_Zoom, 1.f / m_Zoom, 0.001f, 100.f);

        m_IsPerspective = !m_IsPerspective;
        return;
    }
    m_ProjectionMat = glm::perspective(45.0f, m_AspRatio, 0.001f, 100.f);
    m_IsPerspective = !m_IsPerspective;
}

Ray Camera::CreateARay(const float& x, const float& y)
{

    glm::vec3 unprojectedPt = glm::unProject(glm::vec3(x, m_ViewPort.w - 1.0f - y, m_zNear), m_ViewMat, m_ProjectionMat, m_ViewPort);
    
    Ray ray(m_EyePos, unprojectedPt - m_EyePos);
    //For some reason we need to invert the y axis.
    return ray;
}

void Camera::SetViewPort(const unsigned& width, const unsigned& height)
{
    m_ViewPort = glm::ivec4(0,0,width,height);
}

// ---------------- Camera Movement ----------------
void Camera::MoveRight()
{
    m_EyePos += m_SideVec * m_MovementSpeed;
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
}


void Camera::MoveLeft()
{
    m_EyePos -= m_SideVec * m_MovementSpeed;
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
}

void Camera::MoveUp()
{
    m_EyePos += m_UpVec * m_MovementSpeed;
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
}

void Camera::MoveDown()
{
    m_EyePos -= m_UpVec * m_MovementSpeed;
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
}

void Camera::MoveForward()
{
    m_EyePos += m_ViewVec * m_MovementSpeed;
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
}

void Camera::MoveBackward()
{
    m_EyePos -= m_ViewVec * m_MovementSpeed;
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
}

void Camera::Update()
{
    if (m_MovingBF->isMoving && m_MovingBF->isFreeMode)
    {
        m_Acceleration = glm::clamp(m_Acceleration + m_SlopeInc, 0.0f, m_MovementSpeed);
        m_CurrentMovingDir = glm::vec3(0.0f);

        m_CurrentMovingDir -= m_SideVec * (float)m_MovingBF->isRight; // For Right Movement
        m_CurrentMovingDir += m_SideVec * (float)m_MovingBF->isLeft; // For Left Movement

        m_CurrentMovingDir += glm::vec3(0.f, 1.f, 0.f) * (float)m_MovingBF->isUp; // For Upward movement
        m_CurrentMovingDir -= glm::vec3(0.f, 1.f, 0.f) * (float)m_MovingBF->isDown; // For Downward movement

        m_CurrentMovingDir += m_ViewVec * (float)m_MovingBF->isFwd; // For Forward movement
        m_CurrentMovingDir -= m_ViewVec * (float)m_MovingBF->isBack; // For Backward movement
    }
    else
    {
        m_Acceleration = glm::clamp(m_Acceleration - m_SlopeInc, 0.0f, m_MovementSpeed);
    }
    m_EyePos += m_CurrentMovingDir * m_Acceleration;
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
}

template <typename NumType>
void Camera::Yaw(const NumType& step)
{
    float newAzimuth = (this->m_Azimuth + (float)(-step) * m_RotationSpeed);
    this->m_Azimuth = newAzimuth;
    CalculateAndSetVectors();
    m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
}

template <typename NumType>
void Camera::Pitch(const NumType& step)
{
    float newZenith = (this->m_Zenith + (float)step * m_RotationSpeed);
    if (newZenith < (glm::pi<float>() / 2) && newZenith > -(glm::pi<float>() / 2))
    {
        this->m_Zenith = newZenith; //TODO need to take care of rounding zenith % 360;
        CalculateAndSetVectors();
        m_ViewMat = glm::lookTo(m_EyePos, m_ViewVec, m_UpVec);
    }
}

template void Camera::Pitch<float>(const float& step);
template void Camera::Pitch<double>(const double& step);
template void Camera::Pitch<int>(const int& step);

template void Camera::Yaw<float>(const float& step);
template void Camera::Yaw<double>(const double& step);
template void Camera::Yaw<int>(const int& step);


// ---------------------------------------------------------

void Camera::CalculateAndSetVectors()
{
    m_ViewVec = glm::vec3(sin(this->m_Azimuth) * cos(this->m_Zenith),
                          sin(this->m_Zenith),
                          -cos(this->m_Azimuth) * cos(this->m_Zenith));

    m_UpVec = glm::vec3(
        sin(this->m_Azimuth) * cos(this->m_Zenith + glm::pi<float>() / 2),
        sin(this->m_Zenith + glm::pi<float>() / 2),
        -cos(this->m_Azimuth) * cos(this->m_Zenith + glm::pi<float>() / 2));

    m_SideVec = glm::cross(m_UpVec, m_ViewVec);
}

void Camera::RecreateProjectionMat(int width, int height)
{
    m_AspRatio = width / static_cast<float>(height);

    if (m_IsPerspective)
    {
        m_ProjectionMat = glm::perspective(45.0f, m_AspRatio, 0.001f, 100.f);
        return;
    }

    float lowerRatio = (1 / m_AspRatio) * m_Zoom;

    if (m_AspRatio >= 1.f)
        m_ProjectionMat = glm::ortho(-1.f * m_Zoom, 1.f * m_Zoom, -lowerRatio * m_Zoom, lowerRatio * m_Zoom, 0.001f,
                                   100.f);
    else
        m_ProjectionMat = glm::ortho(-lowerRatio * m_Zoom, lowerRatio * m_Zoom, -1.f, 1.f, 0.001f, 100.f);
}
