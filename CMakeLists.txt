cmake_minimum_required(VERSION 3.11)
project(SeaBattle)

set(SOURCE_EXE main.cpp)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_LIB src/GameMenu.cpp)

find_package(SFML REQUIRED COMPONENTS graphics window system)

add_library(GameMenu STATIC ${SOURCE_LIB})
target_include_directories(GameMenu PUBLIC include)


target_link_libraries(GameMenu PUBLIC sfml-graphics sfml-window sfml-system)

add_executable(main ${SOURCE_EXE})

target_link_libraries(main GameMenu)