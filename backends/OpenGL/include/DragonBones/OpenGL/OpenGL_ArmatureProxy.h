#pragma once

#include <vector>

#include <DragonBones/DragonBonesHeaders.h>
#include <DragonBones/OpenGL/OpenGL_Node.h>
#include <DragonBones/OpenGL/OpenGL_Factory.h>
#include <DragonBones/OpenGL/OpenGL_EventDispatcher.h>

#include <glm/glm.hpp>

DRAGONBONES_NAMESPACE_BEGIN

class OpenGL_Display;
class OpenGL_Node;

class OpenGL_ArmatureProxy : public OpenGL_Node, public IArmatureProxy
{
	friend OpenGL_Factory;

protected:
	Armature* _armature = nullptr;
	OpenGL_EventDispatcher _dispatcher;
	glm::vec2 _position;
	std::vector<OpenGL_Node*> _nodes;

protected:
	OpenGL_ArmatureProxy() = default;
	~OpenGL_ArmatureProxy() = default;

public:
	bool hasDBEventListener(const std::string& type) const override { return true; }
	void addDBEventListener(const std::string& type, const std::function<void(EventObject*)>& listener) override;
	void removeDBEventListener(const std::string& type, const std::function<void(EventObject*)>& listener) override;
	void dispatchDBEvent(const std::string& type, EventObject* value) override;

	OpenGL_EventDispatcher* getEventDispatcher() { return &_dispatcher; }

	void addNode(OpenGL_Node* node);
	void removeNode(OpenGL_Node* node);
	void sortNodes();

	void dbInit(Armature* armature) override;
	void dbClear() override;
	void dbUpdate() override;

	void dispose(bool disposeProxy) override;

	Armature* getArmature() const override { return _armature; }
	Animation* getAnimation() const override { return _armature->getAnimation(); }

	void setVisible(bool visible) override;
	void setColor(const glm::vec4& color) override;

	glm::vec4 getBoundingBox() const override;

protected:
	void draw();
};

DRAGONBONES_NAMESPACE_END
