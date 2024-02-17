#https://github.com/meemknight/PikaEngine


cmake_minimum_required(VERSION 3.16)

#I want to link statically to the runtime library. This will help in sharing the game with others
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization


#set glfw to NOT use dynamic runtime and not build unnecessary stuff, do this before declaring projects
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) #under no circumstance we want this to happen so please cmake DON'T compile my project using shared libs

#add third party libraries
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/imgui)
add_subdirectory(third_party/vectormath)
add_subdirectory(third_party/SDL)


if(MSVC)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

#set exe type to be windowed
if(MSVC)
    
     set_target_properties(loopxia-engine PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

endif()

project ("loopxia-engine")

# Add source to this project's executable.
add_executable (loopxia-engine 
"src/test.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET loopxia-engine PROPERTY CXX_STANDARD 20)
endif()

#Define source file macros for the project sources
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_CONFIG CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/config/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_UI CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_EDITOR CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/editor/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_TEST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/test/*.cpp")

file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_CONFIG CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/config/*.h")
file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_EDITOR CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/editor/*.h")
file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_TEST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/test/*.h")

file(GLOB_RECURSE LOOPXIA_ENGINE_API CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/api/*.h")



target_sources(loopxia-engine PRIVATE 
	"${LOOPXIA_ENGINE_HEADER_CONFIG}" "${LOOPXIA_ENGINE_SOURCES_CONFIG}" "${LOOPXIA_ENGINE_SOURCES_UI}" "${LOOPXIA_ENGINE_HEADER_EDITOR}" "${LOOPXIA_ENGINE_SOURCES_EDITOR}" "${LOOPXIA_ENGINE_HEADER_TEST}" "${LOOPXIA_ENGINE_SOURCES_TEST}")

target_include_directories(loopxia-engine PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/api>"
                            "$<INSTALL_INTERFACE:api>" )
                            
set(VECTORMATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/vectormath)
target_include_directories(loopxia-engine PRIVATE "${VECTORMATH_DIR}" )
target_precompile_headers(loopxia-engine
  PUBLIC
    ${VECTORMATH_DIR}/vectormath.hpp
  PRIVATE
)

target_link_libraries(loopxia-engine PRIVATE SDL3-static imgui)

