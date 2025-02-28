project(pstring_pybind LANGUAGES CXX)


aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

pybind11_add_module(pstring_mod 
				${SRC}
)

target_include_directories(pstring_mod PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(pstring_mod PRIVATE
    pstring
    pybind11::module
)

set_target_properties(pstring_mod PROPERTIES
    OUTPUT_NAME "pstring"
    SUFFIX ${PYTHON_MODULE_EXTENSION}
    CXX_STANDARD 20
    CXX_VISIBILITY_PRESET hidden
)

#install(TARGETS pstring_mod
#    DESTINATION bin
#)
