#pragma once
#include <memory>
#include <vector>
#include <glm/ext/matrix_transform.hpp>
#include "../../Buffers/Public/IndexBuffer.h"
#include "../../Buffers/Public/VertexBuffer.h"

#include "Vertex3D.h"

template <typename T>
class Model3D
{
protected:
    /**
     * Even though we would know how many vertices fit inside an array. in C++ you can't create a static-sized array
     * with a size set at runtime. Therefore std::vector is needed.
     */
    std::vector<T> vertices;
    std::vector<unsigned int> indices;

    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;

    glm::mat4 modelMat = glm::identity<glm::mat4>();

    glm::mat4 rotateMat = glm::identity<glm::mat4>();
    glm::mat4 scaleMat = glm::identity<glm::mat4>();
    glm::mat4 translateMat = glm::identity<glm::mat4>();

public:


    /**
     * Creates a vertex buffer.
     * @attention - In order to create a vertex buffer. array vertices has to be filled with data!
     */

    void CreateVertexBuffer();

    /**
     * Creates an index buffer.
     * @attention - In order to create an index buffer. array indices has to be filled with data!
     */

    void CreateIndexBuffer();

    //------------- GETTERS ------------
    [[nodiscard]] glm::mat4 GetModelMat4() const { return modelMat; }
    [[nodiscard]] std::shared_ptr<VertexBuffer> GetVertexBuffer() const { return vertexBuffer; }
    [[nodiscard]] std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return indexBuffer; }
    //----------------------------------

    virtual void Translate(const glm::vec3& vec);
    virtual void rotate(const glm::vec3& vec, const float& angle, const bool& toRadians = true);
    virtual void rotateXYZ(const float& alpha = 0.f, const float& beta = 0.f, const float& gamma = 0.f, const bool& toRadians = true);
    virtual void scale(const glm::vec3& vec);
    virtual void scaleMul(const glm::vec3& vec);

    void setRotationMat(const glm::mat4& mat) {rotateMat = mat;}
    void setScaleMat(const glm::mat4& mat) {scaleMat = mat;}
    void setTranslationMat(const glm::mat4& mat) {translateMat = mat;}

    glm::mat4 calculateModelMat();
    
};
