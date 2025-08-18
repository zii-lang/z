cmake_minimum_required(VERSION 3.20.0)

project(z
	VERSION "1.0.0"
	LANGUAGES C CXX ASM
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_LIST "syntax")

foreach(project ${PROJECT_LIST})
	add_subdirectory(${project})
endforeach()
