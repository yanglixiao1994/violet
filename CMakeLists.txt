cmake_minimum_required (VERSION 3.0)
project (softbody)

find_package(OpenGL REQUIRED)
message(${OPENGL_FOUND})
message(${OPENGL_LIBRARY})
add_subdirectory (external)

cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_executable(
	violet
	source/auxiliary.h
	source/Camera.cpp
	source/Camera.h
	source/Light.cpp
	source/Light.h
	source/Object.h
	source/Object.cpp
	source/oglfw.cpp
	source/Scene.h
	source/Scene.cpp
	source/RenderSystem.h
	source/RenderSystem.cpp
	source/glRenderSystem.h
	source/glRenderSystem.cpp
	source/GpuProgram.h
	source/GpuProgram.cpp
	source/Material.h
	source/Material.cpp
	source/Mesh.h
	source/Mesh.cpp
	source/GpuBuffer.h
	source/GpuBuffer.cpp
	source/phong.vertex
	source/phong.fragment
)
target_link_libraries(
	violet
	${ALL_LIBS}
	assimp
)

#set_target_properties(tutorial04 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/" )
set_target_properties(violet PROPERTIES COMPILE_DEFINITIONS "USE_ASSIMP")
set_target_properties(violet PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/")
create_target_launcher(violet WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/")
