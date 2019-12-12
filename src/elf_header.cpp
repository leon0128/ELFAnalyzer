#include "elf_header.hpp"
#include <iostream>
#include <iomanip>

ELFHeader::ELFHeader():
    mHeader()
{
}

ELFHeader::~ELFHeader()
{
}

bool ELFHeader::load(std::ifstream& stream)
{
    stream.read(reinterpret_cast<char*>(&mHeader),
                sizeof(mHeader));
    
    print();

    return true;
}

void ELFHeader::print() const
{
    std::cout << "===== ELF HEADER =====" << std::endl << std::endl;

    std::cout << "e_ident [0x0] ~ [0x3]: "
              << "0x" << std::hex << static_cast<int>(mHeader.e_ident[0])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[1])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[2])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[3])
              << std::endl;

    std::cout << "e_ident [0x4]        : "
              << "0x" << std::hex << static_cast<int>(mHeader.e_ident[0x4])
              << std::endl;
    std::cout << "e_ident [0x5]        : "
              << "0x" << std::hex << static_cast<int>(mHeader.e_ident[0x5])
              << std::endl;
    std::cout << "e_ident [0x6]        : "
              << "0x" << std::hex << static_cast<int>(mHeader.e_ident[0x6])
              << std::endl;
    std::cout << "e_ident [0x7]        : "
              << "0x" << std::hex << static_cast<int>(mHeader.e_ident[0x7])
              << std::endl;
    std::cout << "e_ident [0x8]        : "
              << "0x" << std::hex << static_cast<int>(mHeader.e_ident[0x8])
              << std::endl;
    std::cout << "e_ident [0x9] ~ [0xf]: "
              << "0x" << std::hex << static_cast<int>(mHeader.e_ident[0x9])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[0xa])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[0xb])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[0xc])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[0xd])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[0xe])
              << ", 0x" << std::hex << static_cast<int>(mHeader.e_ident[0xf])
              << std::endl;

    std::cout << "e_type               : "
              << "0x" << std::hex << mHeader.e_type
              << std::endl;
    std::cout << "e_machine            : "
              << "0x" << std::hex << mHeader.e_machine
              << std::endl;
    std::cout << "e_version            : "
              << "0x" << std::hex << mHeader.e_version
              << std::endl;
    std::cout << "e_entry              : "
              << "0x" << std::hex << std::setw(0x8) << std::setfill('0')
              << mHeader.e_entry << std::endl;
    std::cout << "e_phoff              : "
              << "0x" << std::hex << std::setw(0x8) << std::setfill('0')
              << mHeader.e_phoff << std::endl;
    std::cout << "e_shoff              : "
              << "0x" << std::hex << std::setw(0x8) << std::setfill('0')
              << mHeader.e_shoff << std::endl;
    std::cout << "e_flags              : "
              << "0x" << std::hex << mHeader.e_flags
              << std::endl;
    std::cout << "e_ehsize             : "
              << "0x" << std::hex << mHeader.e_ehsize
              << std::endl;
    std::cout << "e_phentsize          : "
              << "0x" << std::hex << mHeader.e_phentsize
              << std::endl;
    std::cout << "e_phnum              : "
              << "0x" << std::hex << mHeader.e_phnum
              << std::endl;
    std::cout << "e_shentsize          : "
              << "0x" << std::hex << mHeader.e_shentsize
              << std::endl;
    std::cout << "e_shnum              : "
              << "0x" << std::hex << mHeader.e_shnum
              << std::endl;
    std::cout << "shstrndx             : "
              << "0x" << std::hex << mHeader.e_shstrndx
              << std::endl;
}