#pragma once

#include <DragonBones/DragonBonesHeaders.h>
#include <glm/glm.hpp>

DRAGONBONES_NAMESPACE_BEGIN

class OpenGL_ArmatureProxy;
class OpenGL_EventDispatcher;

class OpenGL_ArmatureDisplay
{
private:
	OpenGL_ArmatureProxy* _proxy = nullptr;
	glm::vec2 _pos;

public:
	OpenGL_ArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName = "", const std::string& skinName = "", const std::string& textureAtlasName = "");
	~OpenGL_ArmatureDisplay();

	void setPosition(const glm::vec2& pos) { _pos = pos; }
	const glm::vec2& getPosition() { return _pos; }

	Armature* getArmature() const;
	Animation* getAnimation() const;

	OpenGL_EventDispatcher* getEventDispatcher();

	OpenGL_ArmatureProxy* getArmatureProxy() const;

	glm::vec4 getBoundingBox();

protected:
	void draw() const;
};

DRAGONBONES_NAMESPACE_END
