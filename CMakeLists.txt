cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(Ludum_dare_50_game)

file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE INC "inc/*.hpp")

add_executable(main ${SRC} ${INC})

target_include_directories(main PRIVATE inc)
target_compile_features(main PRIVATE cxx_std_20)
#target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)

#set(SFML_DIR "./lib/SFML/lib/cmake/SFML")
#set(SFML_DIR "C:/DevStuff/SFML/Windows_MinGW_Installed/lib/cmake/SFML")
#set(SFML_STATIC_LIBRARIES TRUE)
#find_package(SFML COMPONENTS system audio window graphics REQUIRED)

target_link_libraries(main sfml-graphics sfml-audio sfml-window sfml-system)

