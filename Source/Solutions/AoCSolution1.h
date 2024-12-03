#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

class AoCSolution1 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
};
