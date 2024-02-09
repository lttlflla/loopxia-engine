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


#declare projects
project(loopxia-engine)

#add engine directory
add_subdirectory(loopxia-engine)

#add third party libraries
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/imgui)
add_subdirectory(third_party/vectormath)


if(MSVC)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

#set exe type to be windowed
if(MSVC)
    
     set_target_properties(loopxia-engine PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

endif()
