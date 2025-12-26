cmake_minimum_required(VERSION 3.30)
project(turtles_journey)

set(CMAKE_CXX_STANDARD 23)
set(MAGIQUE_LAN ON)

add_subdirectory(../magique magique)
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_executable(turtles_journey ${SRC_FILES})

target_include_directories(turtles_journey PRIVATE src ../magique/src)
target_link_libraries(turtles_journey PRIVATE magique)