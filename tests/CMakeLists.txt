set(TESTS ${PROJECT_NAME}-test)

find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${TESTS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/file_creator.cpp
    file_creator_test.cpp
)

target_compile_definitions(${TESTS} PUBLIC TESTS_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(${TESTS} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_compile_features(${TESTS} PRIVATE cxx_std_20)

target_link_libraries(${TESTS} PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
)

include(GoogleTest)