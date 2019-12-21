#include "program_header_table.hpp"
#include "static_data.hpp"
#include <iostream>
#include <iomanip>

const std::unordered_map<std::int32_t, const char*> ProgramHeaderTable::TYPE_MAP
    = {{0x0,          "unknown"}, {0x1, "Loadable segment"}, {0x2, "Dynamic linking info"},
       {0x3, "Interpreter info"}, {0x4,    "Auxiliay info"}, {0x5,             "reserved"},
       {0x6,      "PHT segment"}};

const std::unordered_map<std::int32_t, const char*> ProgramHeaderTable::FLAGS_MAP
    = {{0x0, ""},
       {0x1, "          EXEC "},
       {0x2, "     WRIT "},
       {0x3, "     WRIT EXEC"},
       {0x4, "READ"},
       {0x5, "READ      EXEC"},
       {0x6, "READ WRIT"},
       {0x7, "READ WRIT EXEC"}};

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
                            DATA::ELF().e_phentsize);
        DATA::PHT().push_back(ph);
    }

    return true;
}

void ProgramHeaderTable::print() const
{
    std::cout << "\n\n===== Program Header =====\n\n" << std::endl;
    
    for(std::size_t i = 0; i < DATA::PHT().size(); i++)
    {
        std::cout << "== index : " << i << " ==" << std::endl;

        HEADER::Program& ph = DATA::PHT().at(i);

        std::cout << "p_type   : "
                  << "0x" << std::hex << ph.p_type << std::endl;
        std::cout << "p_flags  : "
                  << "0x" << std::hex << ph.p_flags << std::endl;
        std::cout << "p_offset : "
                  << "0x" << std::setw(0x8) << std::hex << ph.p_offset << std::endl;
        std::cout << "p_vaddr  : "
                  << "0x" << std::setw(0x8) << std::hex << ph.p_vaddr << std::endl;
        std::cout << "p_paddr  : "
                  << "0x" << std::setw(0x8) << std::hex << ph.p_paddr << std::endl;
        std::cout << "p_filesz : "
                  << "0x" << std::hex << ph.p_filesz << std::endl;
        std::cout << "p_memsz  : "
                  << "0x" << std::hex << ph.p_memsz << std::endl;
        std::cout << "p_align  : "
                  << "0x" << std::hex << ph.p_align << std::endl;

        std::cout << std::endl << "= detail = " << std::endl;

        if(ph.p_type >= 0x0 && ph.p_type <= 0x6)
            std::cout << "Type                    : " << TYPE_MAP.at(ph.p_type) << std::endl;
        else
            std::cout << "Type                    : " << "(undefined)" << std::endl;
        std::cout << "Flags                   : " << FLAGS_MAP.at(ph.p_flags) << std::endl;
        std::cout << "File image offset       : "
                  << "0x" << std::setw(0x8) << std::hex << ph.p_offset << std::endl;
        std::cout << "Virtual memory address  : "
                  << "0x" << std::setw(0x8) << std::hex << ph.p_vaddr << std::endl;
        std::cout << "Phisical memory address : "
                  << "0x" << std::setw(0x8) << std::hex << ph.p_paddr << std::endl;
        std::cout << "File image segment size : "
                  << "0x" << std::hex << ph.p_filesz << std::endl;
        std::cout << "Memory segment size     : "
                  << "0x" << std::hex << ph.p_memsz << std::endl;
        std::cout << "Alignment               : "
                  << "0x" << std::hex << ph.p_align << std::endl;
        
        std::cout << std::endl;
    }
}