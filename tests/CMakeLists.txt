# Required packages
find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)
# Define the test executable
add_executable(${TESTS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/file_creator.cpp
    file_creator_test.cpp
)

target_compile_definitions(${TESTS} PUBLIC TESTS_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(${TESTS} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_compile_features(${TESTS} PRIVATE cxx_std_20)

if(DEFINED JSON_SCHEMA_VALIDATOR_CFLAGS_OTHER)
    target_compile_options(${TESTS} PRIVATE ${JSON_SCHEMA_VALIDATOR_CFLAGS_OTHER})
endif()

target_link_libraries(${TESTS} PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator::nlohmann_json_schema_validator
)