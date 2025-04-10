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

TEST_F(file_creator_test, write_and_read_data_from_file)
{
    std::string test_dir = "test_output";
    std::filesystem::create_directory(test_dir);

    std::string file_path = test_dir;
    std::string file_name = "test.json";

    seneca::example::file_creator creator(file_path);

    nlohmann::json json_data = {
        {"name", "Dave"},
        {"language", "C++"}
    };

    creator.create_file(json_data, file_name);

    auto read_data = creator.read_file(file_name);

    EXPECT_EQ(read_data["name"], "Dave");
    EXPECT_EQ(read_data["language"], "C++");

    std::filesystem::remove_all(test_dir);
}
