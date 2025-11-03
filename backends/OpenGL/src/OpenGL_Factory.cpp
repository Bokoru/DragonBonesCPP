#include <DragonBones/OpenGL/OpenGL_Factory.h>

#include <fstream>
#include <sstream>
#include <memory>

#include <DragonBones/OpenGL/OpenGL_Slot.h>
#include <DragonBones/OpenGL/OpenGL_TextureData.h>
#include <DragonBones/OpenGL/OpenGL_TextureAtlasData.h>
#include <DragonBones/OpenGL/OpenGL_ArmatureProxy.h>
#include <DragonBones/OpenGL/OpenGL_Display.h>
#include <DragonBones/OpenGL/OpenGL_EventDispatcher.h>

DRAGONBONES_NAMESPACE_BEGIN

DragonBones* OpenGL_Factory::_dragonBonesInstance;
OpenGL_Factory* OpenGL_Factory::_factory;

OpenGL_Factory::OpenGL_Factory()
{
	_factory = this;

	if (_dragonBonesInstance == nullptr)
	{
		_soundEventDispatcher = std::make_unique<OpenGL_EventDispatcher>();
		_dragonBonesInstance = new DragonBones(_soundEventDispatcher.get());
	}

	_dragonBones = _dragonBonesInstance;
}

OpenGL_Factory::~OpenGL_Factory()
{
	clear();

	if (_dragonBonesInstance)
	{
		delete _dragonBonesInstance;
	}
}

DragonBonesData* OpenGL_Factory::loadDragonBonesData(const std::string& filePath, const std::string& name)
{
	if (!name.empty())
	{
		const auto existedData = getDragonBonesData(name);

		if (existedData)
			return existedData;
	}

	std::stringstream data;

	std::ifstream json(filePath);

	if (json.bad())
		return nullptr;

	data << json.rdbuf();

	if (data.str().empty())
		return nullptr;

	return parseDragonBonesData(data.str().c_str(), name, 1.0f);
}

TextureAtlasData* OpenGL_Factory::loadTextureAtlasData(const std::string& filePath, GLuint atlasTexture, const std::string& name, float scale)
{
	std::stringstream data;

	std::ifstream json(filePath);

	if (json.bad())
		return nullptr;

	data << json.rdbuf();

	if (data.str().empty())
		return nullptr;

	return static_cast<OpenGL_TextureAtlasData*>(BaseFactory::parseTextureAtlasData(data.str().c_str(), atlasTexture, name, scale));
}

OpenGL_ArmatureProxy* OpenGL_Factory::buildArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName, const std::string& skinName, const std::string& textureAtlasName) const
{
	const auto armature = buildArmature(armatureName, dragonBonesName, skinName, textureAtlasName);

	if (armature != nullptr)
	{
		_dragonBones->getClock()->add(armature);

		return static_cast<OpenGL_ArmatureProxy*>(armature->getDisplay());
	}

	return nullptr;
}

GLuint OpenGL_Factory::getTextureDisplay(const std::string& textureName, const std::string& dragonBonesName) const
{
	const auto textureData = static_cast<OpenGL_TextureData*>(_getTextureData(dragonBonesName, textureName));
	if (textureData != nullptr && textureData->texture != nullptr)
	{
		return textureData->texture;
	}

	return nullptr;
}

void OpenGL_Factory::update(float lastUpdate)
{
	_dragonBonesInstance->advanceTime(lastUpdate);
}

TextureAtlasData* OpenGL_Factory::_buildTextureAtlasData(TextureAtlasData* textureAtlasData, void* textureAtlas) const
{
	auto textureAtlasData_ = static_cast<OpenGL_TextureAtlasData*>(textureAtlasData);

	if (textureAtlasData != nullptr)
	{
		if (textureAtlas != nullptr)
		{
			textureAtlasData_->setRenderTexture(static_cast<GLuint>(textureAtlas));
		}
		else
		{
			DRAGONBONES_ASSERT(false, "No atlas texture");
		}
	}
	else
	{
		textureAtlasData_ = BaseObject::borrowObject<OpenGL_TextureAtlasData>();
	}

	return textureAtlasData_;
}

Armature* OpenGL_Factory::_buildArmature(const BuildArmaturePackage& dataPackage) const
{
	const auto armature = BaseObject::borrowObject<Armature>();
	const auto armatureDisplay = new OpenGL_ArmatureProxy();

	armature->init(dataPackage.armature, armatureDisplay, armatureDisplay, _dragonBones);

	return armature;
}

Slot* OpenGL_Factory::_buildSlot(const BuildArmaturePackage& dataPackage, const SlotData* slotData, Armature* armature) const
{
	auto slot = BaseObject::borrowObject<OpenGL_Slot>();
	auto wrapperDisplay = new OpenGL_Display();

	slot->init(slotData, armature, wrapperDisplay, wrapperDisplay);

	return slot;
}

DRAGONBONES_NAMESPACE_END
