#include "file_manager.hpp"
#include <iostream>

bool FileManager::open(std::ifstream& stream,
                       const char* filename,
                       std::ios::openmode mode)
{
    stream.open(filename);
    
    if(!stream.is_open())
    {
        std::cerr << "file-err: cannot open file "
                  << "( " << filename << ")"
                  << std::endl;
        return false; 
    }

    return true;
}

void FileManager::close(std::ifstream& stream)
{
    stream.close();
}