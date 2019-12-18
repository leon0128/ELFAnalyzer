#include "elf_header.hpp"
#include "static_data.hpp"
#include <iostream>
#include <iomanip>

const std::unordered_map<unsigned char, const char*> ELFHeader::BIT_LENGTH_MAP
    = {{0x1, "32 bit"}, {0x2, "64 bit"}};
const std::unordered_map<unsigned char, const char*> ELFHeader::ENDIAN_MAP
    = {{0x1, "Little"}, {0x2, "Big"}};
const std::unordered_map<unsigned char, const char*> ELFHeader::TARGET_OS_ABI_MAP
    = {{0x0,  "System V"}, {0x1,          "HP-UX"}, {0x2,         "NetBSD"}, {0x3,     "Linux"},
       {0x4,  "GNU Hurd"}, {0x6,        "Solaris"}, {0x7,            "AIX"}, {0x8,      "IRIX"},
       {0x9,   "FreeBSD"}, {0xa,          "Tru64"}, {0xb, "Novell Modesto"}, {0xc,   "OpenBSD"},
       {0xd,   "OpenVMS"}, {0xe, "NonStop Kernel"}, {0xf,           "AROS"}, {0x10, "Fenix OS"},
       {0x11, "CloudABI"}};
const std::unordered_map<std::uint16_t, const char*> ELFHeader::TYPE_MAP
    = {{0x00, "unknown"}, {0x01, "Relocatable"}, {0x02, "Executable"}, {0x03, "Shared"}};
const std::unordered_map<std::uint16_t, const char*> ELFHeader::MACHINE_MAP
    = {{0x00, "unknown"}, {0x02,  "SPARC"}, {0x03,     "x86"}, {0x08,   "MIPS"},
       {0x14, "PowerPC"}, {0x16,   "S390"}, {0x28,     "ARM"}, {0x2a, "SuperH"},
       {0x32,   "IA-64"}, {0x3e, "x86-64"}, {0xb7, "AArch64"}, {0xf3, "RISC-V"}};

ELFHeader::ELFHeader()
{
}

ELFHeader::~ELFHeader()
{
}

bool ELFHeader::load() const
{
    DATA::STREAM().seekg(0x0);
    DATA::STREAM().read(reinterpret_cast<char*>(&DATA::ELF()),
                        sizeof(DATA::ELF()));

    if(!check())
        return false;

    print();
    return true;
}

void ELFHeader::print() const
{
    std::cout << "===== ELF HEADER =====" << std::endl << std::endl;

    std::cout << "e_ident [0x0] ~ [0x3]: "
              << "0x"   << std::hex << static_cast<int>(DATA::ELF().e_ident[0])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[1])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[2])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[3])
              << std::endl;

    std::cout << "e_ident [0x4]        : "
              << "0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0x4])
              << std::endl;
    std::cout << "e_ident [0x5]        : "
              << "0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0x5])
              << std::endl;
    std::cout << "e_ident [0x6]        : "
              << "0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0x6])
              << std::endl;
    std::cout << "e_ident [0x7]        : "
              << "0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0x7])
              << std::endl;
    std::cout << "e_ident [0x8]        : "
              << "0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0x8])
              << std::endl;
    std::cout << "e_ident [0x9] ~ [0xf]: "
              << "0x"   << std::hex << static_cast<int>(DATA::ELF().e_ident[0x9])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0xa])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0xb])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0xc])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0xd])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0xe])
              << ", 0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0xf])
              << std::endl;

    std::cout << "e_type               : "
              << "0x" << std::hex << DATA::ELF().e_type
              << std::endl;
    std::cout << "e_machine            : "
              << "0x" << std::hex << DATA::ELF().e_machine
              << std::endl;
    std::cout << "e_version            : "
              << "0x" << std::hex << DATA::ELF().e_version
              << std::endl;
    std::cout << "e_entry              : "
              << "0x" << std::hex << std::setw(0x8) << std::setfill('0')
              << DATA::ELF().e_entry << std::endl;
    std::cout << "e_phoff              : "
              << "0x" << std::hex << std::setw(0x8) << std::setfill('0')
              << DATA::ELF().e_phoff << std::endl;
    std::cout << "e_shoff              : "
              << "0x" << std::hex << std::setw(0x8) << std::setfill('0')
              << DATA::ELF().e_shoff << std::endl;
    std::cout << "e_flags              : "
              << "0x" << std::hex << DATA::ELF().e_flags
              << std::endl;
    std::cout << "e_ehsize             : "
              << "0x" << std::hex << DATA::ELF().e_ehsize
              << std::endl;
    std::cout << "e_phentsize          : "
              << "0x" << std::hex << DATA::ELF().e_phentsize
              << std::endl;
    std::cout << "e_phnum              : "
              << "0x" << std::hex << DATA::ELF().e_phnum
              << std::endl;
    std::cout << "e_shentsize          : "
              << "0x" << std::hex << DATA::ELF().e_shentsize
              << std::endl;
    std::cout << "e_shnum              : "
              << "0x" << std::hex << DATA::ELF().e_shnum
              << std::endl;
    std::cout << "shstrndx             : "
              << "0x" << std::hex << DATA::ELF().e_shstrndx
              << std::endl;

    std::cout << std::endl
              << "== detail ==\n"
              << std::endl;
    std::cout << "Magic number  : "
              << "0x7f, E, L, F"
              << std::endl;
    std::cout << "Bit length    : "
              << BIT_LENGTH_MAP.at(DATA::ELF().e_ident[0x4])
              << std::endl;
    std::cout << "Endian        : "
              << ENDIAN_MAP.at(DATA::ELF().e_ident[0x5])
              << std::endl;
    std::cout << "ELF version   : "
              << "current"
              << std::endl;
    std::cout << "Target OS ABI : "
              << TARGET_OS_ABI_MAP.at(DATA::ELF().e_ident[0x7])
              << std::endl;
    std::cout << "ABI version   : "
              << "0x" << std::hex << static_cast<int>(DATA::ELF().e_ident[0x8])
              << std::endl;
    std::cout << "ELF Type      : "
              << TYPE_MAP.at(DATA::ELF().e_type)
              << std::endl;
    std::cout << "Architecture  : "
              << MACHINE_MAP.at(DATA::ELF().e_machine)
              << std::endl;
    std::cout << "ELF version   : "
              << "original"
              << std::endl;
    std::cout << "Flags         : "
              << std::hex << DATA::ELF().e_flags
              << std::endl;
    std::cout << "ELF Header sz : "
              << "0x" << std::hex << DATA::ELF().e_ehsize
              << std::endl;
    std::cout << "PH entry sz   : "
              << "0x" << std::hex << DATA::ELF().e_phentsize
              << std::endl;
    std::cout << "Number of PH  : "
              << "0x" << std::hex << DATA::ELF().e_phnum
              << std::endl;
    std::cout << "SH entry sz   : "
              << "0x" << std::hex << DATA::ELF().e_shentsize
              << std::endl;
    std::cout << "Number of SH  : "
              << "0x" << std::hex << DATA::ELF().e_shnum
              << std::endl;
    std::cout << "Str table inx : "
              << "0x" << std::hex << DATA::ELF().e_shstrndx
              << std::endl;
    std::cout << "Entry point   : "
              << "0x" << std::setw(0x8) << std::hex << DATA::ELF().e_entry
              << std::endl;
    std::cout << "PHT offset    : "
              << "0x" << std::setw(0x8) << std::hex << DATA::ELF().e_phoff
              << std::endl;
    std::cout << "SHT offset    : "
              << "0x" << std::setw(0x8) << std::hex << DATA::ELF().e_shoff
              << std::endl;
}

bool ELFHeader::check() const
{
    if(DATA::ELF().e_ident[0x0] != 0x7f ||
       DATA::ELF().e_ident[0x1] != 'E'  ||
       DATA::ELF().e_ident[0x2] != 'L'  ||
       DATA::ELF().e_ident[0x3] != 'F')
        return error("incorrect magic number.");
    
    if(DATA::ELF().e_ident[0x4] == 0x1)
        return error("32bit is not supports.");
    else if(DATA::ELF().e_ident[0x4] != 0x2)
        return error("unsupported bit length.");
    
    if(DATA::ELF().e_ident[0x6] != 0x1)
        return error("incorrect elf version.");


    return true;
}

bool ELFHeader::error(const char* message) const
{
    std::cerr << "elf _err: "
              << message
              << std::endl;
    return false;
}
