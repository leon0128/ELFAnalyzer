#pragma once

#include "header.hpp"
#include <unordered_map>

class ProgramHeaderTable
{
private:
    static const std::unordered_map<std::int32_t, const char*> TYPE_MAP;
    static const std::unordered_map<std::int32_t, const char*> FLAGS_MAP;

public:
    ProgramHeaderTable();
    ~ProgramHeaderTable();

    bool load() const;
private:
    void print(const HEADER::Program ph) const;
};