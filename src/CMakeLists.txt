add_library(cclap STATIC
        cclap.cpp
)

target_include_directories(cclap PRIVATE ${cclap_SOURCE_DIR}/include)

set_target_properties(cclap
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
