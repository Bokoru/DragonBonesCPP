
find_package(SFML 3.0.2 COMPONENTS Graphics System REQUIRED)

add_library(DragonBones_SFML STATIC
    "src/SFMLArmatureDisplay.cpp" "include/DragonBones/SFML/SFMLArmatureDisplay.h"
    "src/SFMLArmatureProxy.cpp" "include/DragonBones/SFML/SFMLArmatureProxy.h"
    "include/DragonBones/SFML/SFMLDisplay.h"
    "include/DragonBones/SFML/SFMLEventDispatcher.h"
    "src/SFMLFactory.cpp" "include/DragonBones/SFML/SFMLFactory.h"
    "include/DragonBones/SFML/SFMLNode.h"
    "src/SFMLSlot.cpp" "include/DragonBones/SFML/SFMLSlot.h"
    "src/SFMLTextureAtlasData.cpp" "include/DragonBones/SFML/SFMLTextureAtlasData.h"
    "include/DragonBones/SFML/SFMLTextureData.h"
)
target_include_directories(DragonBones_SFML PUBLIC "include")
target_link_libraries(DragonBones_SFML PUBLIC DragonBones SFML::Graphics)
