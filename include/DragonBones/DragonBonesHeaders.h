/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2018 DragonBones team and other contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the >Software>), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED >AS IS>, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef DRAGONBONES_HEADERS_H
#define DRAGONBONES_HEADERS_H

// core
#include <DragonBones/core/DragonBones.h>
#include <DragonBones/core/BaseObject.h>

// geom
#include <DragonBones/geom/Matrix.h>
#include <DragonBones/geom/Transform.h>
#include <DragonBones/geom/ColorTransform.h>
#include <DragonBones/geom/Point.h>
#include <DragonBones/geom/Rectangle.h>

// model
#include <DragonBones/model/TextureAtlasData.h>
#include <DragonBones/model/UserData.h>
#include <DragonBones/model/DragonBonesData.h>
#include <DragonBones/model/ArmatureData.h>
#include <DragonBones/model/ConstraintData.h>
#include <DragonBones/model/CanvasData.h>
#include <DragonBones/model/SkinData.h>
#include <DragonBones/model/DisplayData.h>
#include <DragonBones/model/BoundingBoxData.h>
#include <DragonBones/model/AnimationData.h>
#include <DragonBones/model/AnimationConfig.h>

// armature
#include <DragonBones/armature/IArmatureProxy.h>
#include <DragonBones/armature/Armature.h>
#include <DragonBones/armature/TransformObject.h>
#include <DragonBones/armature/Bone.h>
#include <DragonBones/armature/Slot.h>
#include <DragonBones/armature/Constraint.h>
#include <DragonBones/armature/DeformVertices.h>

// animation
#include <DragonBones/animation/IAnimatable.h>
#include <DragonBones/animation/WorldClock.h>
#include <DragonBones/animation/Animation.h>
#include <DragonBones/animation/AnimationState.h>
#include <DragonBones/animation/BaseTimelineState.h>
#include <DragonBones/animation/TimelineState.h>

// event
#include <DragonBones/event/EventObject.h>
#include <DragonBones/event/IEventDispatcher.h>

#ifndef EGRET_WASM

// parser
#include <DragonBones/parser/DataParser.h>
#include <DragonBones/parser/JSONDataParser.h>
#include <DragonBones/parser/BinaryDataParser.h>

// factory
#include <DragonBones/factory/BaseFactory.h>
#endif // EGRET_WASM

#endif // DRAGONBONES_HEADERS_H
