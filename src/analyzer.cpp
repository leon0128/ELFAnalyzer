#include "analyzer.hpp"
#include "header.hpp"

#include <fstream>
#include <iostream>

Analyzer::Analyzer()
{
}

Analyzer::~Analyzer()
{
}

bool Analyzer::analyze(char** argv)
{
    std::ifstream stream(argv[1]);
    if(!stream.is_open())
        return false;
    
    HEADER::ELF elf;
    stream.read(reinterpret_cast<char*>(&elf), 0x40);

    std::cout << "=== elf header ===" << std::endl;

    stream.close();
    return true;
}