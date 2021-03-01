cmake_minimum_required(VERSION 3.0.0)
project(MouseClick VERSION 0.1.0)

string(APPEND CMAKE_EXE_LINKER_FLAGS " /MANIFEST:NO")

add_executable(MouseClick WIN32 Resource.rc pch.cpp main.cpp MouseAction.cpp StringTable.cpp)
