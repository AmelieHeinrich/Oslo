//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-03 18:16:57
//

#include <fstream>
#include <sstream>

#include "FileIO.hpp"
#include "Context.hpp"

std::string FileIO::ReadEntireFile(const std::string& path)
{
    std::ifstream stream(path);
    if (!stream.is_open()) {
        LOG_ERROR("Failed to open file! %s", path.c_str());
        return "";
    }

    std::stringstream ss;
    ss << stream.rdbuf();

    stream.close();
    return ss.str();
}

std::vector<std::string> FileIO::ReadLines(const std::string& path)
{
    std::ifstream stream(path);
    std::vector<std::string> lines;
    std::string line;
    
    if (!stream.is_open()) {
        LOG_ERROR("Failed to open file! %s", path.c_str());
        return {};
    }
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    stream.close();
    return lines;
}
