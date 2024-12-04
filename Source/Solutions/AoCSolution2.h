#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

class AoCSolution2 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;

private:

    bool CheckIncreasing(const int32_t A, const int32_t B) const;
    bool CheckDecreasing(const int32_t A, const int32_t B) const;
    bool IsRecordSafe(const vector<int32_t>& Levels) const;

private:
    vector<string> InputData;
};