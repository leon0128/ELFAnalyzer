#include "program_header_table.hpp"
#include "static_data.hpp"

ProgramHeaderTable::ProgramHeaderTable()
{
}

ProgramHeaderTable::~ProgramHeaderTable()
{
}

bool ProgramHeaderTable::load() const
{
    DATA::STREAM().seekg(DATA::ELF().e_phoff);

    HEADER::Program ph;
    for(std::uint16_t i = 0; i < DATA::ELF().e_phnum; i++)
    {
        DATA::STREAM().read(reinterpret_cast<char*>(&ph),
                            sizeof(ph));
    }

    return true;
}