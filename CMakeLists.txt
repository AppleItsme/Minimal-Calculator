cmake_minimum_required(VERSION 3.1...3.24)

project(
	Minimal_Calculator
	VERSION 1.0
	LANGUAGES CXX
	)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

add_library(AST Calculator/AST/AST.cpp Calculator/AST/AST.hpp)
add_library(Processor Calculator/Processor/Processor.cpp Calculator/Processor/Processor.hpp)
add_library(App Calculator/App.cpp Calculator/App.hpp)
target_link_libraries(App PUBLIC AST)
target_link_libraries(App PUBLIC Processor)

add_executable(calculator main.cpp)
target_link_libraries(calculator PRIVATE App)


