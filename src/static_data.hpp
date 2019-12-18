#pragma once

#include "header.hpp"
#include <vector>
#include <fstream>
#include <string>

namespace DATA
{ 
    std::ifstream& STREAM(); // elf file
    const char*& FILENAME();  // file name

    HEADER::ELF& ELF();                  // elf header
    std::vector<HEADER::Program>& PHT(); // program header table
    std::vector<HEADER::Section>& SHT(); // section header table

    std::vector<std::string>& SH_STR_TAB(); // section header string table
};