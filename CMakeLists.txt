cmake_minimum_required(VERSION 3.24)
project(hexxagon_clone)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)
FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(fmt)

add_executable(hexxagon_clone main.cpp
        Controller.cpp
        Controller.h
        Menu.cpp
        Menu.h
        Button.cpp
        Button.h
        Game.cpp
        Game.h
        Hex.cpp
        Hex.h
        HexGrid.cpp
        HexGrid.h
        Colors.h
        BestGame.cpp
        BestGame.h
        LoadGame.cpp
        LoadGame.h
        TextBox.cpp
        TextBox.h)

# Copy the font file to the build directory during build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})


target_link_libraries(hexxagon_clone sfml-graphics)
target_link_libraries(hexxagon_clone fmt)
