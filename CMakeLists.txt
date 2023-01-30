cmake_minimum_required(VERSION 3.10)

project(comlar CXX)

add_library(comlar INTERFACE)
target_compile_features(comlar INTERFACE cxx_std_17)
target_include_directories(comlar INTERFACE include)
install(DIRECTORY include/ DESTINATION include)

add_executable(basic1 example/basic1.cpp)
target_compile_features(basic1 PRIVATE cxx_std_17)
target_include_directories(basic1 PRIVATE include/)

add_executable(basic2 example/basic2.cpp)
target_compile_features(basic2 PRIVATE cxx_std_17)
target_include_directories(basic2 PRIVATE include/)

add_executable(addtional example/addtional.cpp)
target_compile_features(addtional PRIVATE cxx_std_17)
target_include_directories(addtional PRIVATE include/)

