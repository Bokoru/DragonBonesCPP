#pragma once

#include <DragonBones/DragonBonesHeaders.h>
#include <DragonBones/OpenGL/OpenGL_EventDispatcher.h>
#include <glad/gl.h>
#include <memory>

DRAGONBONES_NAMESPACE_BEGIN

class OpenGL_ArmatureProxy;
class OpenGL_TextureData;

class OpenGL_Factory : public BaseFactory
{
protected:
	static DragonBones* _dragonBonesInstance;
	static OpenGL_Factory* _factory;

	std::unique_ptr<OpenGL_EventDispatcher> _soundEventDispatcher;

public:
	OpenGL_Factory();
	~OpenGL_Factory();

public:
	DragonBonesData* loadDragonBonesData(const std::string& filePath, const std::string& name = "");
	TextureAtlasData* loadTextureAtlasData(const std::string& filePath, GLuint atlasTexture, const std::string& name = "", float scale = 1.0f);
	OpenGL_ArmatureProxy* buildArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName = "", const std::string& skinName = "", const std::string& textureAtlasName = "") const;
	GLuint getTextureDisplay(const std::string& textureName, const std::string& dragonBonesName = "") const;

	void addSoundEventListener(const std::function<void(EventObject*)>& listener)
	{
		_soundEventDispatcher->addDBEventListener(EventObject::SOUND_EVENT, listener);
	}

	void update(float lastUpdate);

	static OpenGL_Factory* get() { return _factory; }

protected:
	TextureAtlasData* _buildTextureAtlasData(TextureAtlasData* textureAtlasData, void* textureAtlas) const override;
	Armature* _buildArmature(const BuildArmaturePackage& dataPackage) const override;
	Slot* _buildSlot(const BuildArmaturePackage& dataPackage, const SlotData* slotData, Armature* armature) const override;
};

DRAGONBONES_NAMESPACE_END
