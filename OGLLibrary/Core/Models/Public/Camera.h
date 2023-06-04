#pragma once
#include <glm.hpp>

#include "Ray.h"

struct MovingBitField;

class Camera
{
    
public:
    Camera(const glm::vec3& position, const float& aspectRatio, const glm::ivec2& resolution, const float& a = 0, const float& z = 0);
    ~Camera();

    glm::mat4 getViewMat() const { return m_ViewMat; }
    glm::mat4 getProjectionMat() const { return m_ProjectionMat; }

    void SwitchProjection();
    Ray CreateARay(const float& x, const float& y);

    // ---------------- Getters ------------------

    [[nodiscard]] float GetMovementSpeed() const { return m_MovementSpeed; }
    [[nodiscard]] glm::vec3 GetSideVec() const { return m_SideVec; }
    [[nodiscard]] glm::vec3 GetUpVec() const { return m_UpVec; }
    [[nodiscard]] glm::vec3 GetViewVec() const { return m_ViewVec; }
    [[nodiscard]] glm::vec3 GetPosition() const { return m_EyePos; }
    [[nodiscard]] MovingBitField* GetMovingBitField() const { return m_MovingBF; }

    // ---------------- Setters ------------------
    void SetAspectRatio(const float& ratio) { m_AspRatio = ratio; }
    void SetMovementSpeed(const float& f) { m_MovementSpeed = f; }
    void SetViewPort(const unsigned int& width, const unsigned int& height);

    // ---------------- Camera Movement ----------------
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();
    void MoveForward();
    void MoveBackward();

    void Update();

    void IncMovementSpeed(const float& num)
    {
        m_MovementSpeed = glm::min(m_MovementSpeed + num, m_MovementSpeedMax);
        m_SlopeInc += num * m_SlopeInc/m_MovementSpeed;
    }

    void DecMovementSpeed(const float& num)
    {
        m_MovementSpeed = glm::max(m_MovementSpeed - num, m_MovementSpeedMin);
        m_SlopeInc = glm::max(m_SlopeInc - (num * m_SlopeInc/m_MovementSpeed), 1e-4f);
    }

    template <typename NumType>
    void Yaw(const NumType& step);

    template <typename NumType>
    void Pitch(const NumType& step);
    // ---------------------------------------------------------

    void CalculateAndSetVectors();
    void RecreateProjectionMat(int width, int height);

private:
    
    glm::mat4 m_ViewMat;
    glm::mat4 m_ProjectionMat;
    glm::ivec4 m_ViewPort;
    
    float m_Zoom = 0.75f;
    float m_AspRatio;
    bool m_IsPerspective = true;
    float m_zNear, m_zFar;

    float m_Zenith, m_Azimuth;
    float m_RotationSpeed = 0.01f;

    // Used for the ease-in-out movement of the camera (how much speed will the camera be picking up through time);
    float m_SlopeInc = 0.0005f;
    float m_Acceleration = 0.0f;

    // used as a cap for the acceleration value;
    float m_MovementSpeed, m_MovementSpeedMax, m_MovementSpeedMin;

    MovingBitField* m_MovingBF = nullptr;

    glm::vec3 m_EyePos, m_UpVec, m_ViewVec, m_SideVec;
    glm::vec3 m_CurrentMovingDir;

};


/**
 *  A struct with a bit field to identify in which direction is the camera moving.
 */
struct MovingBitField
{
    bool isFreeMode:1, isMoving:1, isFwd:1, isLeft:1, isBack:1, isRight:1, isUp:1, isDown:1;

    /**
     * Constructs a bit field;
     * @param isFree - Sets a Free mode boolean to indicate that the camera can freely move.
     */
    MovingBitField(bool isFree = true)
        : isFreeMode(isFree), isMoving(false), isFwd(false), isLeft(false),
          isBack(false), isRight(false), isUp(false), isDown(false) {}

    void SetIsMovingForward(bool b)
    {
        isFwd = b;
        CheckIsMoving();
    }
    void SetIsMovingBackwards(bool b)
    {
        isBack = b;
        CheckIsMoving();
    }
    void SetIsMovingLeft(bool b)
    {
        isLeft = b;
        CheckIsMoving();
    }
    void SetIsMovingRight(bool b)
    {
        isRight = b;
        CheckIsMoving();
    }
    void SetIsMovingUp(bool b)
    {
        isUp = b;
        CheckIsMoving();
    }
    void SetIsMovingDown(bool b)
    {
        isDown = b;
        CheckIsMoving();
    }

    void CheckIsMoving() { isMoving = isFwd || isLeft || isBack || isRight || isUp || isDown; }
};
