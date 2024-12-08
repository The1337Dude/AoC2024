#pragma once

#include <vector>
#include <map>

#include "Helpers/AoCHelpers.h"

class AoCSolution5 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;

private:
    int32_t IsValidUpdate(const vector<string>& Update);
    void ReorderUpdate(vector<string>& Update);

private:
    vector<string> InputData;

    map<string, vector<string>> BeforeDataCache;
    map<string, vector<string>> AfterDataCache;

    vector<vector<string>> Updates;
};
