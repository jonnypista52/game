cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES
    main.cpp
    ../../GameLogic/videoGen/videoGen.cpp
)

add_executable(my_project 
    main.cpp

    ../../GameLogic/videoGen/videoGen.cpp
    
)
