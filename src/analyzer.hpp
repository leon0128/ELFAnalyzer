#pragma once

#include <fstream>

class Analyzer
{
public:
    Analyzer();
    ~Analyzer();

    bool analyze(char** argv);
};