if (BUILD_TESTS)
    include (CTest)
    include (Catch)

    add_executable(arg-parser-test arg-parser-test.cpp)
    target_link_libraries(arg-parser-test PRIVATE Catch2::Catch2WithMain PRIVATE cclap) 
    target_include_directories(arg-parser-test PRIVATE ${CMAKE_SOURCE_DIR}/include)

    catch_discover_tests(arg-parser-test)
endif()
