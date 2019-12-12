#pragma once

#include <fstream>

class FileManager
{
public:
    FileManager() = delete;

    static bool open(std::ifstream& stream,
                     const char* filename,
                     std::ios::openmode mode);

    static void close(std::ifstream& stream);
};