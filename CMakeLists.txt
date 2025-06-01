cmake_minimum_required(VERSION 3.16)

if (WIN32)
    add_compile_definitions(LOOPXIA_PLATFORM_WINDOWS WIN32_LEAN_AND_MEAN )
endif (WIN32)

if(MSVC)
    # Default to statically-linked runtime.
    if("${MSVC_RUNTIME}" STREQUAL "")
      set(MSVC_RUNTIME "static")
    endif()
endif()

#I want to link statically to the runtime library. This will help in sharing the game with others
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization


#set glfw to NOT use dynamic runtime and not build unnecessary stuff, do this before declaring projects
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) #under no circumstance we want this to happen so please cmake DON'T compile my project using shared libs

#add third party libraries
#add_subdirectory(third_party/glfw)
#add_subdirectory(third_party/imgui)
add_subdirectory(third_party/SDL)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/glew-cmake)
add_subdirectory(third_party/assimp)
add_subdirectory(third_party/abseil-cpp)


if(MSVC)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

project ("loopxia-engine")

set(LOOPXIA_INCLUDE_DIR "include")
set(LOOPXIA_SOURCE_DIR "src")

# Add source to this project's executable.
add_library (loopxia-engine 

"include/loopxia/object/object.h" 
"include/loopxia/time.h" 
 
"src/loopxia.cpp" 
"src/log.cpp" 
"src/mutex.cpp" 

"include/loopxia/ui.h" 

"include/loopxia/object/camera.h" 
"include/loopxia/object/movable_object.h" 
"include/loopxia/object/instance_tracker.h" 
"include/loopxia/object/transform.h" 

"include/loopxia/render/sprite.h" 
"include/loopxia/render/raymarch.h" 
"include/loopxia/render/billboard.h"
"include/loopxia/render/shader.h" 
"include/loopxia/render/render_buffer.h" 
"include/loopxia/render/mesh_renderer.h" 

"include/loopxia/graph/node.h" 
"include/loopxia/bounding_volume/bounding_volume.h" 

"include/loopxia/scene/scene.h" 
"include/loopxia/scene/script.h" 
"include/loopxia/scene/scriptable_object.h" 
"include/loopxia/scene/hexagon_grid.h" 
"include/loopxia/scene/avatar.h" 
"include/loopxia/scene/scene_transition.h"
 
"include/loopxia/input/keyboard.h" 
"include/loopxia/editor/editor.h" 
"include/loopxia/game/game.h" 
"include/loopxia/game/render_manager.h" 
"include/loopxia/math/math.h" 

"src/bounding_volume/bounding_volume.cpp" 
"src/math/math.cpp" 

"src/render/shader.cpp" 
"src/render/render_buffer.cpp" 
"src/render/mesh_renderer_impl.cpp"
"src/render/mesh_shader_static.cpp"
"src/render/mesh_shader_animated.cpp"
"src/editor/editor.cpp" 

"src/object/camera_impl.h" 
"src/object/transform_impl.h" 
"src/object/object.cpp" 
"src/object/camera_impl.cpp"  
"src/object/transform_impl.cpp" 
"src/object/movable_object_impl.cpp" 

"src/resource/bone_impl.h" 
"src/resource/material_impl.cpp" 
"src/resource/mesh_impl.cpp" 
"src/resource/bone_impl.cpp" 
"src/resource/resource_impl.cpp"
"src/resource/resource_group_impl.cpp"
"src/resource/resource_manager_impl.cpp"
"src/resource/mesh_loader_impl.cpp"
"src/resource/material_loader_impl.cpp"

"src/scene/scene_impl.cpp" 
"src/scene/scene_node_impl.cpp" 
"src/scene/scriptable_object.cpp"
"src/scene/scene_renderer_impl.cpp"
"src/scene/avatar_impl.cpp"

"src/game/game.cpp" 
"src/game/camera_controller_impl.cpp"
"src/render/mesh_renderer_indirect.h" 
"src/render/mesh_renderer_indirect.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET loopxia-engine PROPERTY CXX_STANDARD 20)
endif()

#Define source file macros for the project sources
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_CONFIG CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/config/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_UI CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_EVENT CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/event/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_EDITOR CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/editor/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_TEST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/test/*.cpp")

file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_CONFIG CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/config/*.h")
file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_EDITOR CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/editor/*.h")
file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_TEST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/test/*.h")

file(GLOB_RECURSE LOOPXIA_ENGINE_API CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/loopxia/*.h")

target_sources(loopxia-engine PRIVATE 
"${LOOPXIA_ENGINE_HEADER_CONFIG}"
"${LOOPXIA_ENGINE_SOURCES_CONFIG}"
"${LOOPXIA_ENGINE_SOURCES_EVENT}"
"${LOOPXIA_ENGINE_SOURCES_UI}"
"${LOOPXIA_ENGINE_HEADER_EDITOR}"
"${LOOPXIA_ENGINE_SOURCES_EDITOR}"
"${LOOPXIA_ENGINE_HEADER_TEST}"
"${LOOPXIA_ENGINE_SOURCES_TEST}")

target_include_directories(loopxia-engine PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                            "$<INSTALL_INTERFACE:include>" 
PRIVATE 
"${LOOPXIA_SOURCE_DIR}")
                            
#set(VECTORMATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/vectormath)
#target_include_directories(loopxia-engine PRIVATE "${VECTORMATH_DIR}" )

target_precompile_headers(loopxia-engine
  PUBLIC
   ${LOOPXIA_INCLUDE_DIR}/loopxia/math.h
   ${LOOPXIA_INCLUDE_DIR}/loopxia/log.h
  PRIVATE
   third_party/stb/stb_image.h
   third_party/SDL/include/SDL3/SDL.h
   ${LOOPXIA_INCLUDE_DIR}/loopxia/log.h
)

find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} "third_party")

target_link_libraries(loopxia-engine PRIVATE SDL3-static  assimp absl::synchronization ${OPENGL_LIBRARIES} PUBLIC glm libglew_static)


set(targets loopxia-engine)  # List of target names
foreach(target ${targets})
    get_target_property(INCLUDE_DIRS ${target} INCLUDE_DIRECTORIES)
    message(STATUS "Include directories for target ${target}: ${INCLUDE_DIRS}")
endforeach()

set(SOURCE_ENGINE_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets CACHE INTERNAL "Path to engine asset directory for internal use")

function(copy_engine_assets_dev target output_dir)
    set(DEST_ASSETS_DIR ${output_dir}/assets)

    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying assets from: ${SOURCE_ENGINE_ASSETS_DIR}"
        COMMAND ${CMAKE_COMMAND} -E echo "Copying assets to:   ${DEST_ASSETS_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different  ${SOURCE_ENGINE_ASSETS_DIR} ${DEST_ASSETS_DIR}
        COMMENT "Copying assets from ${SOURCE_ENGINE_ASSETS_DIR} to ${DEST_ASSETS_DIR}"
    )
endfunction()