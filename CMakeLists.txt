cmake_minimum_required(VERSION 3.11)
project(SeaBattle)
set(CMAKE_CXX_STANDARD 20)


find_package(SFML REQUIRED COMPONENTS graphics window system)

add_library(Button STATIC src/Button.cpp)
target_include_directories(Button PUBLIC include)
target_link_libraries(Button PUBLIC sfml-graphics sfml-window sfml-system)


add_library(Screen STATIC src/Screen.cpp)
target_include_directories(Screen PUBLIC include)
target_link_libraries(Screen PUBLIC sfml-graphics sfml-window sfml-system)


add_library(AboutScreen STATIC src/AboutScreen.cpp)
target_include_directories(AboutScreen PUBLIC include)
target_link_libraries(AboutScreen PUBLIC Button)


add_library(GameMenu STATIC src/GameMenuScreen.cpp)
target_include_directories(GameMenu PUBLIC include)
target_link_libraries(GameMenu PUBLIC Screen AboutScreen)


add_executable(main main.cpp)

target_link_libraries(main GameMenu)