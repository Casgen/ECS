#pragma once
#include <fstream>
#include <signal.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>


#define ASSERT(x) if (!(x)) raise(SIGTRAP)

namespace Utils
{
    static std::string ReadFile(const std::string& filename)
    {
      std::cout << "message" << std::endl;
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
