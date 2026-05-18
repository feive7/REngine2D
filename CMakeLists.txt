cmake_minimum_required(VERSION 3.10)
project(rengine2d)

if(WIN32)
set(raylib_DIR "../Libraries/raylib")
endif()

set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED)
add_executable(${PROJECT_NAME} main.cpp "engine/Engine.h" "engine/Object.h"  )
target_link_libraries(${PROJECT_NAME} raylib)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
