cmake_minimum_required(VERSION 3.20)
project(ShadowMap VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# библотека из движков
add_library(CoreEngine 
    Engines/AstronomyEngine.cpp
    Engines/ShadowEngine.cpp
)

target_include_directories(CoreEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(.)

add_executable(
    ShadowMap
    main.cpp
)


# линкую CoreEngine т.е 2 файла, они собраны в библиотеку CoreEngine
target_link_libraries(ShadowMap PRIVATE CoreEngine)


# тесты из папки Tests а также включение файла теста из cmake'а тестирования
enable_testing()
add_subdirectory(Tests)
