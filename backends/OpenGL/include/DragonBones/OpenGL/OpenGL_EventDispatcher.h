#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

#include <DragonBones/DragonBonesHeaders.h>
DRAGONBONES_NAMESPACE_BEGIN

class OpenGL_EventDispatcher : public IEventDispatcher
{
	using Func_t = std::function<void(EventObject*)>;

private:
	std::unordered_map<std::string, std::vector<Func_t>> _listeners;

	bool _enabled = true;

public:
	OpenGL_EventDispatcher() = default;
	~OpenGL_EventDispatcher() = default;

	void setEnabled(bool enabled) { _enabled = enabled; }

	void addDBEventListener(const std::string& type, const Func_t& listener) override
	{
		_listeners[type].push_back(listener);
	}

	void removeDBEventListener(const std::string& type, const Func_t& listener) override
	{
		// TODO
	}

	void dispatchDBEvent(const std::string& type, EventObject* value) override
	{
		if (!_enabled)
			return;

		for (auto& listener : _listeners[type])
		{
			listener(value);
		}
	}

	bool hasDBEventListener(const std::string& type) const { return true; };
};

DRAGONBONES_NAMESPACE_END
