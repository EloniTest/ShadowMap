add_executable(RunTests
    test_main.cpp)

target_link_libraries(RunTests PRIVATE CoreEngine)

add_test(NAME AllRightTest COMMAND RunTests)

