#include "file_creator.hpp"

#include <gtest/gtest.h>
// #include <spdlog/spdlog.h>
#include <filesystem>

namespace
{

    class file_creator_test : public ::testing::Test
    {
    protected:
        file_creator_test() {

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
            {"students", {{{"id", 1}, {"name", "Dave"}}}}};

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
            {"name", "NotValid"}};

        EXPECT_THROW({ creator.create_file(invalid_json, file_name); }, std::runtime_error);

        std::filesystem::remove_all(test_dir);
    }

    TEST_F(file_creator_test, create_file_to_nonexistent_directory_should_throw)
    {
        std::string file_path = "non_existent_dir";
        std::string file_name = "fail.json";

        seneca::example::file_creator creator(file_path);

        nlohmann::json valid_json = {
            {"students", {{{"id", 42}, {"name", "Alice"}}}}};

        EXPECT_THROW({ creator.create_file(valid_json, file_name); }, std::runtime_error);
    }

    TEST_F(file_creator_test, read_file_should_return_json)
    {
        std::string test_dir = "test_output";
        std::filesystem::create_directory(test_dir);
        std::string file_path = test_dir;
        std::string file_name = "read.json";

        seneca::example::file_creator creator(file_path);

        nlohmann::json valid_json = {
            {"students", {{{"id", 1}, {"name", "Dave"}}}}};

        creator.create_file(valid_json, file_name);

        nlohmann::json result = creator.read_file(file_name);

        EXPECT_EQ(result["students"][0]["id"], 1);
        EXPECT_EQ(result["students"][0]["name"], "Dave");

        std::filesystem::remove_all(test_dir);
    }

    // Read_file function
    TEST_F(file_creator_test, read_file_with_valid_json_should_return_data)
    {
        std::string test_dir = "test_output";
        std::filesystem::create_directory(test_dir);
        std::string file_path = test_dir;
        std::string file_name = "students.json";

        std::ofstream(test_dir + "/" + file_name) << R"({
        "students": [
            { "id": 1, "name": "Dave" },
            { "id": 2, "name": "Olivia" }
        ]
    })";

        seneca::example::file_creator creator(file_path);

        auto result = creator.read_file(file_name);

        ASSERT_TRUE(result.contains("students"));
        ASSERT_EQ(result["students"].size(), 2);
        EXPECT_EQ(result["students"][1]["name"], "Olivia");

        std::filesystem::remove_all(test_dir);
    }
    TEST_F(file_creator_test, read_file_with_invalid_json_should_throw)
    {
        std::string test_dir = "test_output";
        std::filesystem::create_directory(test_dir);
        std::string file_path = test_dir;
        std::string file_name = "not_json.txt";

        std::ofstream(test_dir + "/" + file_name) << "This is not JSON";

        seneca::example::file_creator creator(file_path);

        EXPECT_THROW({ creator.read_file(file_name); }, std::runtime_error);

        std::filesystem::remove_all(test_dir);
    }
    TEST_F(file_creator_test, read_file_with_invalid_schema_should_throw)
    {
        std::string test_dir = "test_output";
        std::filesystem::create_directory(test_dir);
        std::string file_path = test_dir;
        std::string file_name = "bad_schema.json";

        std::ofstream(test_dir + "/" + file_name) << R"({
        "students": [
            { "name": "Missing ID" }
        ]
    })";

        seneca::example::file_creator creator(file_path);

        EXPECT_THROW({ creator.read_file(file_name); }, std::runtime_error);

        std::filesystem::remove_all(test_dir);
    }
}
