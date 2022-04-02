cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project(Ludum_dare_50_game)

include_directories(inc)
include_directories(src)

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(main ${SRC})
target_link_libraries(main sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(main ${OPENGL_LIBRARIES})
set_property(TARGET main PROPERTY CXX_STANDARD 20)
