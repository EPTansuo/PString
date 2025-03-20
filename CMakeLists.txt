cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(pstring VERSION 1.0.0)

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


install(EXPORT pstringTargets
    FILE pstringTargets.cmake
    DESTINATION lib/cmake/pstring
)


include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/pstringConfig.cmake
    INSTALL_DESTINATION lib/cmake/pstring
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/pstringConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pstringConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/pstringConfigVersion.cmake
    DESTINATION lib/cmake/pstring
)

