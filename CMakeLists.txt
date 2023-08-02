cmake_minimum_required(VERSION 3.11)
project(SeaBattle)
set(CMAKE_CXX_STANDARD 20)


find_package(SFML REQUIRED COMPONENTS graphics window system)

add_library(Screen STATIC src/Screen.cpp)
target_include_directories(Screen PUBLIC include)
target_link_libraries(Screen PUBLIC sfml-graphics sfml-window sfml-system)

add_library(GameMenu STATIC src/GameMenu.cpp)
target_include_directories(GameMenu PUBLIC include)
target_link_libraries(GameMenu PUBLIC Screen)


add_executable(main main.cpp)

target_link_libraries(main GameMenu)