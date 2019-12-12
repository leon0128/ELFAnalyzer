#include "analyzer.hpp"
#include "file_manager.hpp"
#include "elf_header.hpp"

#include <fstream>
#include <iostream>

Analyzer::Analyzer():
    mStream()
{
}

Analyzer::~Analyzer()
{
}

bool Analyzer::analyze(char** argv)
{
    if(!FileManager::open(mStream, argv[1], std::ios::binary))
        return false;

    ELFHeader elf;
    elf.load(mStream);

    FileManager::close(mStream);
    return true;
}