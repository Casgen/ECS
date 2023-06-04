#include "../public/Model3D.h"
#include "../../Constants.h"
#include "../public/Axis.h"
#include "../public/VertexPos.h"
#include "../../../Utils/Utils.h"


template <typename T>
void Model3D<T>::CreateVertexBuffer()
{
    ASSERT(!vertices.empty());
    vertexBuffer = std::make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(T));
}

template void Model3D<Vertex3D>::CreateVertexBuffer();
template void Model3D<VertexLine>::CreateVertexBuffer();
template void Model3D<VertexPos>::CreateVertexBuffer();


template <typename T>
void Model3D<T>::CreateIndexBuffer()
{
    ASSERT(!indices.empty());
    indexBuffer = std::make_shared<IndexBuffer>(indices.data(), indices.size());
}

template void Model3D<Vertex3D>::CreateIndexBuffer();
template void Model3D<VertexLine>::CreateIndexBuffer();
template void Model3D<VertexPos>::CreateIndexBuffer();


template <typename T>
void Model3D<T>::Translate(const glm::vec3& vec)
{
    translateMat = glm::translate(glm::identity<glm::mat4>(), vec);
    calculateModelMat();
}

template void Model3D<Vertex3D>::Translate(const glm::vec3& vec);
template void Model3D<VertexLine>::Translate(const glm::vec3& vec);
template void Model3D<VertexPos>::Translate(const glm::vec3& vec);

template <typename T>
void Model3D<T>::rotate(const glm::vec3& vec, const float& angle, const bool& toRadians)
{
    float newAngle = angle;
    
    if (toRadians) newAngle = angle * (180/glm::pi<float>());
    rotateMat = glm::rotate(glm::identity<glm::mat4>(), newAngle, vec);
    
    rotateMat = glm::rotate(glm::identity<glm::mat4>(), newAngle, vec);
    
    calculateModelMat();
}

template void Model3D<Vertex3D>::rotate(const glm::vec3& vec, const float& angle, const bool& toRadians);
template void Model3D<VertexLine>::rotate(const glm::vec3& vec, const float& angle, const bool& toRadians);
template void Model3D<VertexPos>::rotate(const glm::vec3& vec, const float& angle, const bool& toRadians);


template <typename T>
void Model3D<T>::rotateXYZ(const float& alpha, const float& beta, const float& gamma, const bool& toRadians)
{
    float newAlpha = alpha;
    float newBeta = beta;
    float newGamma = gamma;
    
    if (toRadians)
    {
        constexpr float unitOfPi = 180/glm::pi<float>();
        newAlpha = alpha * unitOfPi;
        newBeta = beta * unitOfPi;
        newGamma = gamma * unitOfPi;
    }

    const glm::mat4 rotateMatX = glm::rotate(glm::identity<glm::mat4>(), newAlpha, Constants::xAxisVec);
    const glm::mat4 rotateMatY = glm::rotate(rotateMatX, newBeta, Constants::yAxisVec);
    rotateMat = glm::rotate(rotateMatY, newGamma, Constants::zAxisVec); // rotateMatZ assigned directly to rotateMat.
    
    calculateModelMat();
}

template void Model3D<Vertex3D>::rotateXYZ(const float& alpha, const float& beta, const float& gamma, const bool& toRadians);
template void Model3D<VertexLine>::rotateXYZ(const float& alpha, const float& beta, const float& gamma, const bool& toRadians);
template void Model3D<VertexPos>::rotateXYZ(const float& alpha, const float& beta, const float& gamma, const bool& toRadians);


template <typename T>
void Model3D<T>::scale(const glm::vec3& vec)
{
    scaleMat = glm::scale(glm::identity<glm::mat4>(), vec);
    calculateModelMat();
}

template void Model3D<Vertex3D>::scale(const glm::vec3& vec);
template void Model3D<VertexLine>::scale(const glm::vec3& vec);
template void Model3D<VertexPos>::scale(const glm::vec3& vec);


template <typename T>
void Model3D<T>::scaleMul(const glm::vec3& vec)
{
    scaleMat = glm::scale(scaleMat, vec);
    calculateModelMat();
}

template void Model3D<Vertex3D>::scaleMul(const glm::vec3& vec);
template void Model3D<VertexLine>::scaleMul(const glm::vec3& vec);
template void Model3D<VertexPos>::scaleMul(const glm::vec3& vec);


template <typename T>
glm::mat4 Model3D<T>::calculateModelMat()
{
    modelMat = translateMat * scaleMat * rotateMat;
    return modelMat;
}
    
template glm::mat4 Model3D<Vertex3D>::calculateModelMat();
template glm::mat4 Model3D<VertexLine>::calculateModelMat();
template glm::mat4 Model3D<VertexPos>::calculateModelMat();
