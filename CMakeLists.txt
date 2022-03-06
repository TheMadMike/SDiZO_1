# Copyright 2022 by Michał Gibas

project(sdizo C CXX)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(SOURCES
src/main.cpp)

set(TARGET_NAME
sdizo)

add_executable(${TARGET_NAME} ${SOURCES})