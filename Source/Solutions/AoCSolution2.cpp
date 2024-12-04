#include "AoCSolution2.h"

void AoCSolution2::Initialize(const vector<string>& Input)
{
    InputData = Input;
}

string AoCSolution2::GetResult(const int Part)
{
    int32_t NumSafeRecords = 0;
    bool bUseProblemDampener = true;
    if (Part == 1)
    {
        bUseProblemDampener = false;
    }

    for (const auto& InputRecord : InputData)
    {
        const auto Tokens = AoCHelpers::Tokenize(InputRecord, ' ');
        const vector<int32_t> Levels = AoCHelpers::Convert(Tokens);

        bool bIsRecordSafe = false;
        bIsRecordSafe = IsRecordSafe(Levels);
        if (bUseProblemDampener)
        {
            for (int32_t Index = 0; Index < Levels.size(); Index++)
            {
                if (bIsRecordSafe)
                {
                    break;
                }
                auto SubLevels = Levels;
                SubLevels.erase(SubLevels.begin() + Index);
                bIsRecordSafe |= IsRecordSafe(SubLevels);
            }
        }

        if (bIsRecordSafe)
        {
            NumSafeRecords++;
        }
    }

    return to_string(NumSafeRecords);
}

bool AoCSolution2::CheckIncreasing(const int32_t A, const int32_t B) const
{
    const auto Diff = (B - A);
    bool bIsIncreasing = Diff >= 1 && Diff <= 3;

    return bIsIncreasing;
}

bool AoCSolution2::CheckDecreasing(const int32_t A, const int32_t B) const
{
    const auto Diff = (B - A);
    const bool bIsDecreasing = Diff <= -1 && Diff >= -3;

    return bIsDecreasing;
}

bool AoCSolution2::IsRecordSafe(const vector<int32_t>& Levels) const
{
    bool bIsIncreasing = false;
    bool bIsDecreasing = false;

    for (int32_t Index = 0; Index < (Levels.size() - 1); Index++)
    {
        const auto CurrentLevel = Levels[Index];
        const auto NextLevel = Levels[Index + 1];

        auto bCurrentIsIncreasing = CheckIncreasing(CurrentLevel, NextLevel);
        auto bCurrentIsDecreasing = CheckDecreasing(CurrentLevel, NextLevel);

        if (Index == 0)
        {
            bIsIncreasing = bCurrentIsIncreasing;
            bIsDecreasing = bCurrentIsDecreasing;
        }
        else
        {
            bIsIncreasing &= bCurrentIsIncreasing;
            bIsDecreasing &= bCurrentIsDecreasing;
        }
    }

    return  bIsIncreasing ^ bIsDecreasing;
}
