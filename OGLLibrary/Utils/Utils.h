#pragma once
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>


#define ASSERT(x) if (!(x)) __debugbreak()

namespace Utils
{
    static std::string ReadFile(const std::string& filename)
    {
        std::ifstream stream(filename);

        if (!stream.is_open())
            throw std::runtime_error("Failed to open file! " + filename + "\n");

        std::string line;
        std::stringstream strStream;
        while (std::getline(stream, line))
        {
            strStream << line << "\n";
        }

        return strStream.str();
    }
};
