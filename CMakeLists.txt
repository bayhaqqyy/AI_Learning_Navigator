cmake_minimum_required(VERSION 3.16)
project(AILearningNavigator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ai_algorithms
    src/algorithms.cpp
    src/data.cpp
)
target_include_directories(ai_algorithms PUBLIC include)

add_executable(ai_learning_navigator src/main.cpp)
target_link_libraries(ai_learning_navigator PRIVATE ai_algorithms)

add_executable(test_algorithms tests/test_algorithms.cpp)
target_link_libraries(test_algorithms PRIVATE ai_algorithms)

enable_testing()
add_test(NAME algorithm_tests COMMAND test_algorithms)