# Find package GLM
find_package(glm CONFIG REQUIRED)

# Compile OpenGL backend library
add_library(DragonBones_OpenGL STATIC
    # Glad
    "glad/src/gl.c"

    # Backend Source
    "src/OpenGL_Factory.cpp" "include/DragonBones/OpenGL/OpenGL_Factory.h"
)

# Setup includes and linker targets
target_include_directories(DragonBones_OpenGL PUBLIC "include" "glad/include")
target_link_libraries(DragonBones_OpenGL PUBLIC DragonBones glm)
