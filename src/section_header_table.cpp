#include "section_header_table.hpp"
#include "static_data.hpp"

#include <iostream>
#include <iomanip>

SectionHeaderTable::SectionHeaderTable()
{
}

SectionHeaderTable::~SectionHeaderTable()
{
}

bool SectionHeaderTable::load() const
{
    DATA::STREAM().seekg(DATA::ELF().e_shoff);

    HEADER::Section sh;
    for(std::int16_t i = 0; i < DATA::ELF().e_shnum; i++)
    {
        DATA::STREAM().read(reinterpret_cast<char*>(&sh),
                            DATA::ELF().e_shentsize);
        DATA::SHT().push_back(sh);
    }
    
    loadShStrTab();

    print();

    return true;
}

void SectionHeaderTable::loadShStrTab() const
{
    HEADER::Section sh = DATA::SHT().at(DATA::ELF().e_shstrndx);

    DATA::STREAM().seekg(sh.sh_offset);

    std::string str;
    for(std::size_t i = 0; i < sh.sh_size; i++)
    {
        char c = 0x0;
        DATA::STREAM().read(&c, 0x1);
        if(c != 0x0)
            str.push_back(c);
        else
        {
            str.push_back(c);
            DATA::SH_STR_TAB().push_back(str);
            str.clear();
        }
    }
}

void SectionHeaderTable::print() const
{
    std::cout << "\n\n\n" << std::endl;

    for(std::size_t i = 0; i < DATA::SHT().size(); i++)
    {
        HEADER::Section& sh = DATA::SHT().at(i);

        std::cout << std::endl << "===== Section Header =====" << std::endl << std::endl;

        std::cout << "sh_name      : "
                  << "0x" << std::hex << sh.sh_name << std::endl;
        std::cout << "sh_type      : "
                  << "0x" << std::hex << sh.sh_type << std::endl;
        std::cout << "sh_flags     : "
                  << "0x" << std::hex << sh.sh_flags << std::endl;
        std::cout << "sh_addr      : "
                  << "0x" << std::setw(0x8) << std::hex << sh.sh_addr << std::endl;
        std::cout << "sh_offset    : "
                  << "0x" << std::hex << sh.sh_offset << std::endl;
        std::cout << "sh_size      : "
                  << "0x" << std::hex << sh.sh_size << std::endl;
        std::cout << "sh_link      : "
                  << "0x" << std::hex << sh.sh_link << std::endl;
        std::cout << "sh_info      : "
                  << "0x" << std::hex << sh.sh_info << std::endl;
        std::cout << "sh_addralign : "
                  << "0x" << std::hex << sh.sh_addralign << std::endl;
        std::cout << "sh_entsize   : "
                  << "0x" << std::hex << sh.sh_entsize << std::endl;

        std::cout << std::endl << "== detail ==" << std::endl;
    }
}