#pragma once

#include <fstream>
#include <unordered_map>

class ELFHeader
{
private:
    static const std::unordered_map<unsigned char, const char*> BIT_LENGTH_MAP;
    static const std::unordered_map<unsigned char, const char*> ENDIAN_MAP;
    static const std::unordered_map<unsigned char, const char*> TARGET_OS_ABI_MAP;
    static const std::unordered_map<std::uint16_t, const char*> TYPE_MAP;
    static const std::unordered_map<std::uint16_t, const char*> MACHINE_MAP;

public:
    ELFHeader();
    ~ELFHeader();

    bool load() const;

private:
    void print() const;
    bool check() const;
    bool error(const char* message) const;
};