cmake_minimum_required(VERSION 3.10)

# Set project name
project(OPENGL_LIB VERSION 1.0)

if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Define the source files
set(SOURCES
	main.cpp
	source/Camera.cpp
	source/Cubex.cpp
	source/Cylinder.cpp 
	source/HollowCube.cpp 
	source/HollowCylinder.cpp 
	source/Jaw.cpp 
	source/Light.cpp 
	source/Mesh.cpp 
	source/Object.cpp 
	source/Plane.cpp 
	source/Renderer.cpp 
	source/Scene.cpp 
	source/Sphere.cpp
	source/Transform.cpp 
	source/VertexArray.cpp 
	source/VertexBufferLayout.cpp 
	source/buffers/IndexBuffer.cpp 
	source/buffers/VertexBuffer.cpp 
	source/shader/Shader.cpp 
	source/test/ClearColor.cpp 
	source/test/Cube.cpp 
	source/test/Scenery.cpp 
	source/test/Test.cpp 
	source/test/TestMenu.cpp 
	source/test/Texture2D.cpp 
	source/texture/Texture.cpp 
	include/vendor/imgui/imgui.cpp	
	include/vendor/imgui/imgui_draw.cpp 
	include/vendor/imgui/imgui_demo.cpp		
	include/vendor/imgui/imgui_widgets.cpp 
	include/vendor/imgui/imgui_impl_glfw.cpp
	include/vendor/imgui/imgui_impl_opengl3.cpp
	include/vendor/imgui/imgui_tables.cpp
)

# Define header files

set(HEADERS 
	include/Camera.hpp
	include/Cubex.hpp
	include/Cylinder.hpp 
	include/HollowCube.hpp 
	include/HollowCylinder.hpp 
	include/Jaw.hpp 
	include/Light.hpp 
	include/Mesh.hpp 
	include/Object.hpp 
	include/Plane.hpp 
	include/Renderer.hpp 
	include/Scene.hpp 
	include/Sphere.hpp
	include/Transform.hpp 
	include/VertexArray.hpp 
	include/VertexBufferLayout.hpp 
	include/buffers/IndexBuffer.hpp 
	include/buffers/VertexBuffer.hpp 
	include/shader/Shader.hpp 
	include/test/ClearColor.hpp 
	include/test/Cube.hpp 
	include/test/Scenery.hpp 
	include/test/Test.hpp 
	include/test/TestMenu.hpp 
	include/test/Texture2D.hpp 
	include/texture/Texture.hpp 
	include/vendor/imgui/imgui.h 
	include/vendor/imgui/imgui_impl_glfw.h 
	include/vendor/imgui/imgui_impl_opengl3.h
#	include/vendor/stb_image/stb_image.h
)

# Add executables
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Find Opengl package

find_package(OpenGL REQUIRED)

# Variables for external library locations
set(GLFW_DIR "" CACHE PATH "Path to the GLFW library")
set(GLEW_DIR "" CACHE PATH "Path to the GLEW library")

# Add GLFW library
if (NOT EXISTS ${GLFW_DIR})
    message(FATAL_ERROR "GLFW directory not found. Please set the GLFW_DIR variable.")
endif()

# Include the GLFW headers
include_directories(${GLFW_DIR}/include)

# Link the GLFW library (assuming the library files are in ${GLFW_DIR}/lib or similar)
set(GLFW_LIBRARY ${GLFW_DIR}/lib-vc2022/glfw3.lib)
# Link the GLFW library
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})

#add_subdirectory(${GLFW_DIR} ${CMAKE_SOURCE_DIR}/glfw)
#target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_DIR}/include)
#target_link_libraries(${PROJECT_NAME} glfw)

# Add GLEW library manually
if (NOT EXISTS ${GLEW_DIR})
    message(FATAL_ERROR "GLEW directory not found. Please set the GLEW_DIR variable.")
endif()

# Assuming GLEW is provided as a precompiled library

set(GLEW_ROOT ${GLEW_DIR})
set(GLEW_INCLUDE_DIRS ${GLEW_DIR}/include)
set(GLEW_LIBRARIES ${GLEW_DIR}/lib)
set(GLEW_USE_STATIC_LIBS ON) 
message(GLEW_ROOT_PATH="${GLEW_ROOT}")
message(GLEW_INCLUDE_DIR_PATH="${GLEW_INCLUDE_DIRS}")
message(GLEW_LIBRARIES_PATH="${GLEW_LIBRARIES}")
find_package(GLEW REQUIRED)

# Check if GLEW library is found
if (GLEW_NOT_FOUND)
    message(FATAL_ERROR "GLEW library not found. Please check the GLEW_DIR variable.")
else ()
	message(HURRAY_MESSAGE="HAPPY DAYS!")
endif()
target_link_libraries(${PROJECT_NAME} glfw GLEW::GLEW)



# Link the GLEW library
#target_include_directories(${GLEW_LIGBRARY} PUBLIC ${GLEW_DIR}/include/GL)
#target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARY})




# Add GLM include directory
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${PROJECT_SOURCE_DIR}/vendor/glm)

message(SOURCE_DIR=${PROJECT_SOURCE_DIR})

# Add stb_image library
add_library(stb_image STATIC source/vendor/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC ${PROJECT_SOURCE_DIR}/include/vendor/stb_image)	
target_link_libraries(${PROJECT_NAME} stb_image)

# Add ImGui library
add_library(imgui STATIC 
	include/vendor/imgui/imgui.cpp	
	include/vendor/imgui/imgui_draw.cpp 
	include/vendor/imgui/imgui_demo.cpp		
	include/vendor/imgui/imgui_widgets.cpp 
	include/vendor/imgui/imgui_impl_glfw.cpp
	include/vendor/imgui/imgui_impl_opengl3.cpp
	include/vendor/imgui/imgui_tables.cpp
)
target_include_directories(imgui PUBLIC include/vendor/imgui)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
	OpenGL::GL
	glm 
	imgui 
)
 
# Include directories

target_include_directories(${PROJECT_NAME} PUBLIC
	${PROJECT_SOURCE_DIR}/include 
	${PROJECT_SOURCE_DIR}/include/vendor/imgui 
#	${PROJECT_SOURCE_DIR}/include/vendor/stb_image 
	${PROJECT_SOURCE_DIR}/include/vendor/glm
)