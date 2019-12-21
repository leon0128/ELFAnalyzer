#pragma once

#include <unordered_map>
#include <vector>

class SectionHeaderTable
{
private:
    static const std::unordered_map<std::int32_t, const char*>     TYPE_MAP;
    static const std::vector<std::pair<std::int64_t, const char*>> FLAG_MAP;

public:
    SectionHeaderTable();
    ~SectionHeaderTable();

    bool load() const;
    void print() const;

private:
    void loadShStrTab() const;
};