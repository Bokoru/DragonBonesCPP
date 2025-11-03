cmake_minimum_required (VERSION 3.20)
project (DragonBones)

# Compile Options
option(DRAGONBONES_BACKEND_OPENGL "Compile the OpenGL backend" ON)

# Third Party Packages
find_package(simdjson CONFIG REQUIRED)

# DragonBones static library
add_library(DragonBones STATIC
    # Animation
    "src/animation/Animation.cpp" "include/DragonBones/animation/Animation.h"
    "src/animation/AnimationState.cpp" "include/DragonBones/animation/AnimationState.h"
    "src/animation/BaseTimelineState.cpp" "include/DragonBones/animation/BaseTimelineState.h"
    "src/animation/TimelineState.cpp" "include/DragonBones/animation/TimelineState.h"
    "src/animation/WorldClock.cpp" "include/DragonBones/animation/WorldClock.h"
    "include/DragonBones/animation/IAnimatable.h"
    
    # Armature
    "src/armature/Armature.cpp" "include/DragonBones/armature/Armature.h"
    "src/armature/Bone.cpp" "include/DragonBones/armature/Bone.h"
    "src/armature/Constraint.cpp" "include/DragonBones/armature/Constraint.h"
    "src/armature/DeformVertices.cpp" "include/DragonBones/armature/DeformVertices.h"
    "src/armature/Slot.cpp" "include/DragonBones/armature/Slot.h"
    "src/armature/TransformObject.cpp" "include/DragonBones/armature/TransformObject.h"
    "include/DragonBones/armature/IArmatureProxy.h"

    # Core
    "src/core/BaseObject.cpp" "include/DragonBones/core/BaseObject.h"
    "src/core/DragonBones.cpp" "include/DragonBones/core/DragonBones.h"

    # Event
    "src/event/EventObject.cpp" "include/DragonBones/event/EventObject.h"
    "include/DragonBones/event/IEventDispatcher.h"

    # Factory
    "src/factory/BaseFactory.cpp" "include/DragonBones/factory/BaseFactory.h"

    # Geom
    "include/DragonBones/geom/ColorTransform.h"
    "include/DragonBones/geom/Matrix.h"
    "src/geom/Point.cpp" "include/DragonBones/geom/Point.h"
    "include/DragonBones/geom/Rectangle.h"
    "src/geom/Transform.cpp" "include/DragonBones/geom/Transform.h"
    
    # Model
    "src/model/AnimationConfig.cpp" "include/DragonBones/model/AnimationConfig.h"
    "src/model/AnimationData.cpp" "include/DragonBones/model/AnimationData.h"
    "src/model/ArmatureData.cpp" "include/DragonBones/model/ArmatureData.h"
    "src/model/BoundingBoxData.cpp" "include/DragonBones/model/BoundingBoxData.h"
    "src/model/CanvasData.cpp" "include/DragonBones/model/CanvasData.h"
    "src/model/ConstraintData.cpp" "include/DragonBones/model/ConstraintData.h"
    "src/model/DisplayData.cpp" "include/DragonBones/model/DisplayData.h"
    "src/model/DragonBonesData.cpp" "include/DragonBones/model/DragonBonesData.h"
    "src/model/SkinData.cpp" "include/DragonBones/model/SkinData.h"
    "src/model/TextureAtlasData.cpp" "include/DragonBones/model/TextureAtlasData.h"
    "src/model/UserData.cpp" "include/DragonBones/model/UserData.h"

    # Parser
    "src/parser/JSONDataParser.cpp" "include/DragonBones/parser/JSONDataParser.h"
    "src/parser/DataParser.cpp" "include/DragonBones/parser/DataParser.h"
    "src/parser/BinaryDataParser.cpp" "include/DragonBones/parser/BinaryDataParser.h"
)

# Specify include directories for dependant projects.
target_include_directories(DragonBones PUBLIC "include")

# Link against third party libraries.
target_link_libraries(DragonBones PUBLIC simdjson::simdjson)
