cmake_minimum_required(VERSION 3.11)
project(SeaBattle)
set(CMAKE_CXX_STANDARD 20)

find_package(SFML REQUIRED COMPONENTS graphics window system)

add_library(Classes STATIC src/Button.cpp src/Screen.cpp)
target_include_directories(Classes PUBLIC include)
target_link_libraries(Classes PUBLIC sfml-graphics sfml-window sfml-system)

add_executable(main main.cpp src/AboutScreen.cpp src/GameMenuScreen.cpp src/ButtonEventProcessor.cpp)

target_link_libraries(main Classes)