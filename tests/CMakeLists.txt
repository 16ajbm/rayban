cmake_minimum_required(VERSION 3.15) set(CMAKE_CXX_STANDARD 17)

    set(TEST_EXECUTABLE rayban_tests)

        add_executable(${TEST_EXECUTABLE} tests.cpp tuple_test.cpp)

            target_link_libraries(${TEST_EXECUTABLE} ${Boost_LIBRARIES})

                target_include_directories(${TEST_EXECUTABLE} PRIVATE ${Boost_INCLUDE_DIRS}../
                                           include)

                    add_test(NAME ${TEST_EXECUTABLE} COMMAND ${TEST_EXECUTABLE})