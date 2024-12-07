#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

enum class EOperationType : uint8_t
{
    None,
    Mult,
    Do,
    Dont,
};

class AoCSolution3 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;

private:
    pair<EOperationType, int32_t> GetOperation(const string& OperationString, const int32_t Pos) const;
    int32_t GetOperationValue(const string& OperationString) const;
    int32_t GetPrefixStringIndex(const string& PrefixString) const;
    bool GetPrefixStringValue(const string& PrefixString) const;

private:
    vector<string> InputData;
};