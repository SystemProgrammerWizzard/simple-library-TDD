#include "file_creator.hpp"

#include <gtest/gtest.h>
// #include <spdlog/spdlog.h>
#include <filesystem>

namespace
{

class file_creator_test : public ::testing::Test
{
protected:

    file_creator_test()
    {

    };

    void SetUp()
    {

    }

    void TearDown()
    {

    }
};

    TEST_F(file_creator_test, create_file_with_valid_json_should_pass)
    {
        std::string test_dir = "test_output";
        std::filesystem::create_directory(test_dir);
        std::string file_path = test_dir;
        std::string file_name = "valid.json";

        seneca::example::file_creator creator(file_path);

        nlohmann::json valid_json = {
            {"students", {
                { {"id", 1}, {"name", "Dave"} }
            }}
        };

        EXPECT_NO_THROW({
            creator.create_file(valid_json, file_name);
        });

        std::filesystem::remove_all(test_dir);
    }

    TEST_F(file_creator_test, create_file_with_invalid_schema_should_throw)
    {
        std::string test_dir = "test_output";
        std::filesystem::create_directory(test_dir);
        std::string file_path = test_dir;
        std::string file_name = "invalid_schema.json";

        seneca::example::file_creator creator(file_path);

        nlohmann::json invalid_json = {
            {"name", "NotValid"}
        };

        EXPECT_THROW({
            creator.create_file(invalid_json, file_name);
        }, std::runtime_error);

        std::filesystem::remove_all(test_dir);
    }

    TEST_F(file_creator_test, create_file_to_nonexistent_directory_should_throw)
{
    std::string file_path = "non_existent_dir";
    std::string file_name = "fail.json";

    seneca::example::file_creator creator(file_path);

    nlohmann::json valid_json = {
        {"students", {
            { {"id", 42}, {"name", "Alice"} }
        }}
    };

    EXPECT_THROW({
        creator.create_file(valid_json, file_name);
    }, std::runtime_error);
}

    TEST_F(file_creator_test, read_file_should_return_json)
    {
        std::string test_dir = "test_output";
        std::filesystem::create_directory(test_dir);
        std::string file_path = test_dir;
        std::string file_name = "read.json";

        seneca::example::file_creator creator(file_path);

        nlohmann::json valid_json = {
            {"students", {
                { {"id", 1}, {"name", "Dave"} }
            }}
        };

        creator.create_file(valid_json, file_name);

        nlohmann::json result = creator.read_file(file_name);

        EXPECT_EQ(result["students"][0]["id"], 1);
        EXPECT_EQ(result["students"][0]["name"], "Dave");

        std::filesystem::remove_all(test_dir);
    }
}
