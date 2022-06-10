cmake_minimum_required(VERSION 3.21)
project(prediction-trie)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(
        Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(prediction-trie PredictionTrie.cpp PredictionTrie.h main.cpp UI.h UI.cpp)

target_link_libraries(
        prediction-trie
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)