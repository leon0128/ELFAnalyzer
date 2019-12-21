#include "section_header_table.hpp"
#include "static_data.hpp"

#include <iostream>
#include <iomanip>

const std::unordered_map<std::int32_t, const char*> SectionHeaderTable::TYPE_MAP
    = {{0x00,      "unknown"}, {0x01, "Program data"},
       {0x02, "Symbol table"}, {0x03, "String table"},
       {0x04, "Relocation entries with addends"},
       {0x05, "Symbol hash table"},
       {0x06, "Dynamic linking info"},
       {0x07, "Notes"},
       {0x08, "bss (Program space with no data)"},
       {0x09, "Relocation entries, no addends"},
       {0x0a, "Reserved"},
       {0x0b, "Dynamic linker symbol table"},
       {0x0e, "Array of constructors"},
       {0x0f, "Array of destructors"},
       {0x10, "Array of pre-constructors"},
       {0x11, "Section group"},
       {0x12, "Extended section indices"},
       {0x13, "Number of defined types"}};

const std::vector<std::pair<std::int64_t, const char*>> SectionHeaderTable::FLAG_MAP
    = {{0x00000001, "WRITE"},
       {0x00000002, "ALLOC"},
       {0x00000004, "EXECU"},
       {0x00000010, "MERGE"},
       {0x00000020, "STRIN"},
       {0x00000040, "ILINK"},
       {0x00000080, "LINKO"},
       {0x00000100, "OSNON"},
       {0x00000200, "GROUP"},
       {0x00000400, "THLOD"},
       {0x0ff00000, "OSSPE"},
       {0xf0000000, "PRSPE"},
       {0x40000000, "ORDER"},
       {0x80000000, "EXCLU"}};

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
    std::cout << "\n\n===== Section Header =====\n\n" << std::endl;

    for(std::size_t i = 0; i < DATA::SHT().size(); i++)
    {
        HEADER::Section& sh = DATA::SHT().at(i);

        std::cout << "== index : " << i << " ==" << std::endl;

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

        std::cout << std::endl << "= detail =" << std::endl;
        
        std::cout << "Name       : ";
        HEADER::Section& shStrTab = DATA::SHT().at(DATA::ELF().e_shstrndx);
        DATA::STREAM().seekg(shStrTab.sh_offset + sh.sh_name);
        while(1)
        {
            char c = 0x0;
            DATA::STREAM().read(&c, 0x1);
            if(c != 0x0)
                std::cout << c;
            else
                break;
        }
        std::cout << std::endl;

        try
        {
            std::cout << "Type       : "
                      << TYPE_MAP.at(sh.sh_type) << std::endl;
        }
        catch(const std::out_of_range& error)
        {
            std::cout << "Type       : "
                      << "undefined" << std::endl;
        }

        std::cout << "Flags      : ";
        for(auto&& pair : FLAG_MAP)
        {
            if(pair.first & sh.sh_flags)
                std::cout << pair.second << " ";
        }
        std::cout << std::endl;

        std::cout << "Address    : "
                  << "0x" << std::setw(0x8) << std::hex << sh.sh_addr << std::endl;
        std::cout << "Offset     : "
                  << "0x" <<std::setw(0x8) << std::hex << sh.sh_offset << std::endl;
        std::cout << "Size       : "
                  << "0x" << std::hex << sh.sh_size << std::endl;
        std::cout << "Link index : "
                  << "0x" << std::hex << sh.sh_link << std::endl;
        std::cout << "Infomation : "
                  << "0x" << std::hex << sh.sh_info << std::endl;
        std::cout << "Alignment  : "
                  << "0x" << std::hex << sh.sh_addralign << std::endl;
        std::cout << "Entry size : "
                  << "0x" << std::hex << sh.sh_entsize << std::endl;
        std::cout << std::endl;
    }
}