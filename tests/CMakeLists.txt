add_executable(resource_tests
        tests.cpp
)

target_link_libraries(resource_tests PRIVATE
        resource_core
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(resource_tests)
