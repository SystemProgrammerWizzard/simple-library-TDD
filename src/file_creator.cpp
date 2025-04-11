#include "file_creator.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace seneca::example {

file_creator::file_creator(std::string& file_path)
    : m_file_path(file_path)
{
    std::cout << "Files will be created in " << m_file_path << std::endl;
    if (!fs::exists(m_file_path)) {
        fs::create_directories(m_file_path);
    }
}

file_creator::~file_creator()
{
    std::cout << "Destructor" << std::endl;
}

void file_creator::create_file(nlohmann::json& json_object, std::string& file_name)
{
    fs::path full_path = fs::path(m_file_path) / file_name;
    std::ofstream ofs(full_path);
    if (!ofs) {
        throw std::runtime_error("Cannot open file for writing: " + full_path.string());
    }
    ofs << json_object.dump(4);
    std::cout << "Created File: " << full_path << std::endl;
}

nlohmann::json file_creator::read_file(std::string& file_name)
{
    fs::path full_path = fs::path(m_file_path) / file_name;
    std::ifstream ifs(full_path);
    if (!ifs) {
        throw std::runtime_error("Cannot open file for reading: " + full_path.string());
    }
    nlohmann::json json_object;
    ifs >> json_object;
    std::cout << "Read File: " << full_path << std::endl;
    return json_object;
}

}