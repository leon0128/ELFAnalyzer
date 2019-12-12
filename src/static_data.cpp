#include "static_data.hpp"

HEADER::ELF elf;

HEADER::ELF& DATA::ELF()
{
    return elf;
}