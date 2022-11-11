cmake_minimum_required(VERSION 3.1...3.24)

project(
	Minimal_Calculator
	VERSION 1.0
	LANGUAGES CXX
	)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Wall")

add_library(Postfix Calculator/Postfix/Postfix.cpp Calculator/Postfix/Postfix.hpp)
add_library(Processor Calculator/Processor/Processor.cpp Calculator/Processor/Processor.hpp)
add_library(App Calculator/App.cpp Calculator/App.hpp)
target_link_libraries(App PUBLIC Postfix)
target_link_libraries(App PUBLIC Processor)

add_executable(calculator main.cpp)
target_link_libraries(calculator PRIVATE App)
target_compile_features(calculator PRIVATE cxx_std_20)


