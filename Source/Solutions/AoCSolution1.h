#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

class AoCSolution1 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;

private:
    pair<vector<int32_t>, vector<int32_t>> GetLists() const;
    void SortList(vector<int32_t>& List);

    int32_t GetDistanceBetweenLists(const pair<vector<int32_t>, vector<int32_t>>& Lists);
    int32_t GetSimilarityBetweenLists(const pair<vector<int32_t>, vector<int32_t>>& Lists);
private:
    vector<string> InputData;
};