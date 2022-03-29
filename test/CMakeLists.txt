if (BUILD_TESTS)
    include (CTest)
    include (Catch)

    add_executable(arg-parser-test arg-parser-test.cpp)
    target_link_libraries(arg-parser-test PRIVATE Catch2::Catch2WithMain PRIVATE cclap) 
    target_include_directories(arg-parser-test PRIVATE ${CMAKE_SOURCE_DIR}/include)

    add_executable(example-usage example-usage.cpp)
    target_link_libraries(example-usage PRIVATE Catch2::Catch2WithMain PRIVATE cclap) 
    target_include_directories(example-usage PRIVATE ${CMAKE_SOURCE_DIR}/include)

    catch_discover_tests(arg-parser-test)
    catch_discover_tests(example-usage)
endif()
