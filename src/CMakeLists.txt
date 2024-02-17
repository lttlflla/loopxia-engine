# CMakeList.txt : CMake project for loopxia-engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("loopxia-engine")

# Add source to this project's executable.
add_executable (loopxia-engine "loopxia-engine.cpp" "loopxia-engine.h" "ui/ui.h" "ui/ui.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET loopxia-engine PROPERTY CXX_STANDARD 20)
endif()

#Define source file macros for the project sources
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_CONFIG CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/config/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_EDITOR CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/editor/*.cpp")
file(GLOB_RECURSE LOOPXIA_ENGINE_SOURCES_TEST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_CONFIG CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/config/*.h")
file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_EDITOR CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/editor/*.h")
file(GLOB_RECURSE LOOPXIA_ENGINE_HEADER_TEST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h")

target_sources(loopxia-engine PRIVATE 
	"${LOOPXIA_ENGINE_HEADER_CONFIG}" "${LOOPXIA_ENGINE_SOURCES_CONFIG}" "${LOOPXIA_ENGINE_HEADER_EDITOR}" "${LOOPXIA_ENGINE_SOURCES_EDITOR}" "${LOOPXIA_ENGINE_HEADER_TEST}" "${LOOPXIA_ENGINE_SOURCES_TEST}")

target_link_libraries(loopxia-engine PRIVATE SDL3-static imgui)

