
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(nlohmann_json REQUIRED)


set (CMAKE_CXX_STANDARD 20)

if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIRS})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif()

add_library(${PROJECT_NAME}-lib STATIC
    file_creator.cpp
)

target_link_libraries(${PROJECT_NAME}-lib PUBLIC
    nlohmann_json::nlohmann_json
)

target_compile_features(${PROJECT_NAME}-lib PUBLIC cxx_std_20)

include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME}-lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)