#pragma once

#include "header.hpp"
#include <fstream>

class ELFHeader
{
public:
    ELFHeader();
    ~ELFHeader();

    bool load(std::ifstream& stream);

    void print() const;
private:
    HEADER::ELF mHeader;
};