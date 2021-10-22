cmake_minimum_required(VERSION 3.20)

set(CMAKE_PREFIX_PATH "${QTDIR}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(obs-pipewire
    VERSION 0.0.1
    LANGUAGES C
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(PipeWire REQUIRED)
find_package(LibObs REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)


add_library(obs-pipewire SHARED 
    "src/main.c"
)
target_include_directories(obs-pipewire PUBLIC "src")

target_link_libraries(obs-pipewire PipeWire::PipeWire)
target_link_libraries(obs-pipewire libobs)