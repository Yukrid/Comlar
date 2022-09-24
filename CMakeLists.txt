cmake_minimum_required(VERSION 3.10)

project(comlar CXX)

add_library(comlar INTERFACE)
target_compile_features(comlar INTERFACE cxx_std_14)
target_include_directories(comlar INTERFACE include)
install(DIRECTORY include/ DESTINATION include)
