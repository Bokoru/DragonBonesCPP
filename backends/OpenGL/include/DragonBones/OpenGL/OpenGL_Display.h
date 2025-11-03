#pragma once

#include <vector>
#include <DragonBones/DragonBonesHeaders.h>
#include <DragonBones/OpenGL/OpenGL_Node.h>

DRAGONBONES_NAMESPACE_BEGIN

struct Vertex {
    glm::vec2 position;
    glm::u8vec4 color;
};

struct BlendMode {
    GLenum srcColor;
    GLenum dstColor;
    GLenum eqColor;
    GLenum srcAlpha;
    GLenum dstAlpha;
    GLenum eqAlpha;
};

class OpenGL_Display : public OpenGL_Node
{
    static void transformRect(glm::mat3& transform, glm::vec4& rect)
    {
        glm::vec2 p00, p01, p10, p11;
        p00 = {rect.x, rect.y};
        p11 = {rect.z, rect.w};
        p01 = {p00.x, p11.y};
        p10 = {p11.x, p00.y};

        p00 = transform * glm::vec3(p00, 1.f);
        p01 = transform * glm::vec3(p01, 1.f);
        p10 = transform * glm::vec3(p10, 1.f);
        p11 = transform * glm::vec3(p11, 1.f);

        rect = 
        { 
            glm::min(glm::min(p00, p01), glm::min(p10, p11)), 
            glm::max(glm::max(p00, p01), glm::max(p10, p11)) 
        };
    }

public:
    const GLuint texture = 0;

    GLuint vao, vbo, ebo;

    bool modified;
    std::vector<unsigned short> indices;
    std::vector<Vertex> vertices;
    BlendMode blendMode;
    GLenum primitiveType = GL_TRIANGLE_STRIP;

    OpenGL_Display() = default;
    ~OpenGL_Display() = default;

    void setColor(const glm::vec4& color) override
    {
        for (auto& vert : vertices)
        {
            vert.color = glm::u8vec4(color * glm::vec4(0xFF));
        }

        modified = true;
    }

    glm::vec4 getBoundingBox() const override
    {
        if (texture == 0)
            return glm::vec4(0.f);

        if (vertices.empty())
            return glm::vec4(0.f);

        glm::vec2 min = vertices[0].position;
        glm::vec2 max = vertices[0].position;

        for (auto& vert : vertices)
        {
            min = glm::min(min, vert.position);
            max = glm::max(max, vert.position);
        }

        glm::vec4 rect(min, max - min);

        glm::mat3 matrix = _transform;
        transformRect(matrix, rect);

        return rect;
    }

protected:
    void draw(void(*set_texture)(GLuint), void(*push_transform)(const glm::mat3&), void(*pop_transform)())
    {
        // Don't do anything if invisible.
        if (!_visible) return;
        
        // Update the array buffers if modified.
        if (modified)
        {
            // Update the vertex buffer.
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the vertex buffer.

            // Update the element buffer.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the element buffer.
        }

        // Enable blending.
        glEnable(GL_BLEND);

        // Set the blend functions and equations.
        glBlendFuncSeparate(blendMode.srcColor, blendMode.dstColor, blendMode.srcAlpha, blendMode.dstAlpha);
        glBlendEquationSeparate(blendMode.eqColor, blendMode.eqAlpha);

        // Set the current texture.
        if (set_texture != nullptr)
            set_texture(texture);

        // Push the current transform.
        if (push_transform != nullptr) 
            push_transform(_transform);

        // Draw the vertex array.
        glBindVertexArray(vao);
        glDrawElements(primitiveType, indices.size(), GL_UNSIGNED_SHORT, nullptr);
        glBindVertexArray(0); // Unbind the vertex array.

        // Pop the current transform.
        if ((push_transform != nullptr) && (pop_transform != nullptr)) 
            pop_transform();

        // Disable blending.
        glDisable(GL_BLEND);
    }
};

DRAGONBONES_NAMESPACE_END
