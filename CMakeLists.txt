cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(PyDeath VERSION 1.0.0)

# Set up the mod binary
add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/pybindings.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

set(FETCHCONTENT_TIMEOUT 100000000)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
set(IMGUI_VERSION "v1.90.8")
CPMAddPackage("gh:matcool/gd-imgui-cocos#...")
CPMAddPackage(
    NAME ImGuiColorTextEdit
    GITHUB_REPOSITORY BalazsJako/ImGuiColorTextEdit
    GIT_TAG origin/master  # Replace with the tag or commit hash you want to use
)
CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11
    VERSION 2.9.0 # specify the version you need
)

target_link_libraries(${PROJECT_NAME} pybind11::embed)
target_link_libraries(${PROJECT_NAME} pybind11::module)
target_link_libraries(${PROJECT_NAME} imgui-cocos)
target_link_libraries(${PROJECT_NAME} ImGuiColorTextEdit)

setup_geode_mod(${PROJECT_NAME})
