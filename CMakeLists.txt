cmake_minimum_required(VERSION 3.10)

project(pstring)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)


find_package(pybind11 REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(difftest)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


install(TARGETS pstring
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

