cmake_minimum_required(VERSION 3.13)

project(basic-opengl-basic)

add_executable(${PROJECT_NAME}
	src/main.cpp
)

add_subdirectory(ext/glfw)

target_include_directories(${PROJECT_NAME} 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext
)

target_link_directories(${PROJECT_NAME}
	PRIVATE ext/glfw/src
)

target_link_libraries(${PROJECT_NAME} glfw "-framework OpenGL")