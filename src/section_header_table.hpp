#pragma once

class SectionHeaderTable
{
public:
    SectionHeaderTable();
    ~SectionHeaderTable();

    bool load() const;

private:
    void loadShStrTab() const;
    void print() const;
};