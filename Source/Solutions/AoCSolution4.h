#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

class AoCSolution4 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
    vector<string> GetSearchStringsFromPosition(const int32_t Row, const int32_t Column);
    // bool DFS(const int32_t Row, const int32_t Column, const string& Prefix) const;

private:
    vector<string> InputData;
};