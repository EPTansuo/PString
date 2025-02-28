cmake_minimum_required(VERSION 3.10)

project(pstring)

set(CMAKE_CXX_STANDARD 11)

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/)

add_subdirectory(src)
add_subdirectory(test)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


install(TARGETS pstring)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)

