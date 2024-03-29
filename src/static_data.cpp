#include "static_data.hpp"

std::ifstream stream;
const char* filename = nullptr;

HEADER::ELF elf;
std::vector<HEADER::Program> pht;
std::vector<HEADER::Section> sht;

std::vector<std::string> shStrTab;

std::ifstream& DATA::STREAM()
{
    return stream;
}

const char*& DATA::FILENAME()
{
    return filename;
}

HEADER::ELF& DATA::ELF()
{
    return elf;
}

std::vector<HEADER::Program>& DATA::PHT()
{
    return pht;
}

std::vector<HEADER::Section>& DATA::SHT()
{
    return sht;
}

std::vector<std::string>& DATA::SH_STR_TAB()
{
    return shStrTab;
}