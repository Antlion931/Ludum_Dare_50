cmake_minimum_required(VERSION 3.4.0 FATAL_ERROR)
project(Ludum_dare_50_game)

option(STATIC_LIBS "Set static build" OFF)

file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE INC "inc/*.hpp")

add_executable(main ${SRC} ${INC})

target_include_directories(main PRIVATE inc)
target_compile_features(main PRIVATE cxx_std_20)
#target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)

if(STATIC_LIBS)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

set(SFML_DIR "./lib/SFML/lib/cmake/SFML")
find_package(SFML COMPONENTS system audio window graphics REQUIRED)

#set(SFML_DIR "C:/DevStuff/SFML/Windows_MinGW_Installed/lib/cmake/SFML")

target_link_libraries(main sfml-graphics sfml-audio)

