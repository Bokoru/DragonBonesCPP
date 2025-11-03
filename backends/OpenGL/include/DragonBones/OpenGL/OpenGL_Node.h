#pragma once

#include <DragonBones/DragonBonesHeaders.h>
#include <glm/glm.hpp>

DRAGONBONES_NAMESPACE_BEGIN

class OpenGL_Node
{
protected:
	glm::mat3 _transform;
	bool _visible = true;
	int _zOffset = 0;

public:
	OpenGL_Node() = default;
	virtual ~OpenGL_Node() = default;

	void setZOffset(int zOffset) { _zOffset = zOffset; }
	int getZOffset() const { return _zOffset; }

	void setMatrix(const Matrix& matrix, const glm::vec2& offset, float scaleX, float scaleY)
	{
		_transform = glm::mat3(
			matrix.a * scaleX, matrix.c * scaleY, offset.x,
			matrix.b * scaleX, matrix.d * scaleY, offset.y,
			0.f, 0.f, 1.f
		);
	}

	virtual void setVisible(bool visible) { _visible = visible; }

	virtual void setColor(const glm::vec4& color) = 0;

	virtual glm::vec4 getBoundingBox() const = 0;
};

DRAGONBONES_NAMESPACE_END
