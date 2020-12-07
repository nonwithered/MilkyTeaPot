SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

project(demo)

include_directories(
    ../include
)

link_directories(
    ../../target/debug
)

add_executable(a
    main.cc
)

target_link_libraries(a
    milk_powder
)