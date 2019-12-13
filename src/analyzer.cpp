#include "analyzer.hpp"
#include "file_manager.hpp"
#include "elf_header.hpp"
#include "program_header_table.hpp"
#include "static_data.hpp"

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
    DATA::FILENAME() = argv[1];
    if(!FileManager::open(DATA::STREAM(), DATA::FILENAME(), std::ios::binary))
        return false;

    ELFHeader elf;
    elf.load();
    ProgramHeaderTable pht;
    pht.load();
    

    FileManager::close(DATA::STREAM());
    return true;
}