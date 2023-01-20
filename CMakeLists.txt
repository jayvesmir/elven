cmake_minimum_required(VERSION 3.14)
project(elven)

set(CMAKE_EXPORT_COMPILE_COMANDS on)
set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${PROJECT_NAME}
    src/Ayanami.cpp
    src/Image.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src/include)