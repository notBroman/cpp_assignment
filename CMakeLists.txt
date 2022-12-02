cmake_minimum_required(VERSION 3.4)
set(CMAKE_BUILD_TYPE Debug)


project(cpp_assignment LANGUAGES CXX)

add_executable(a.out
    src/main.cpp
    #src/tester.cpp
    src/cpp_part1_FlightTimetableEntry.cpp
)

target_compile_features(a.out PUBLIC cxx_std_11)

function(print)
    foreach(var ${ARGN})
        message("${var} = ${${var}}")
    endforeach()
endfunction()

print(PROJECT_NAME)
