#include "AoCSolution5.h"

void AoCSolution5::Initialize(const vector<string>& Input)
{
    InputData = Input;
    int32_t Index = 0;
    for (; Index < InputData.size(); Index++)
    {
        if (InputData[Index].empty())
        {
            break;
        }

        const auto Tokens = AoCHelpers::Tokenize(InputData[Index], '|');
        if (Tokens.size() != 2)
        {
            continue;
        }
        BeforeDataCache[Tokens[0]].push_back(Tokens[1]);
        AfterDataCache[Tokens[1]].push_back(Tokens[0]);
    }
    Index++;

    for (; Index < InputData.size(); Index++)
    {
        auto Tokens = AoCHelpers::Tokenize(InputData[Index], ',');
        Updates.push_back(move(Tokens));
    }
}

string AoCSolution5::GetResult(const int Part)
{
    int32_t Result = 0;

    for (auto& Update : Updates)
    {
        if (IsValidUpdate(Update))
        {
            if (Part == 1)
            {
                Result += atoi(Update[Update.size()/2].data());
            }
        }
        else
        {
            if (Part == 2)
            {
                ReorderUpdate(Update);
                Result += atoi(Update[Update.size()/2].data());
            }
        }
    }

    return to_string(Result);
}

int32_t AoCSolution5::IsValidUpdate(const vector<string>& Update)
{
    for (int32_t Index = 0; Index < Update.size(); Index++)
    {
        const auto& CurrentPage = Update[Index];
        vector<string> AfterUpdateList(Update.begin() + Index, Update.end());
        vector<string> BeforeUpdateList(Update.begin(), Update.begin() + Index);

        for (const auto& AfterUpdate : AfterDataCache[CurrentPage])
        {
            for (const auto& AfterUpdateListItem : AfterUpdateList)
            {
                if (AfterUpdate == AfterUpdateListItem)
                {
                    return false;
                }
            }
        }

        for (const auto& BeforeUpdate : BeforeDataCache[CurrentPage])
        {
            for (const auto& BeforeUpdateListItem : BeforeUpdateList)
            {
                if (BeforeUpdate == BeforeUpdateListItem)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void AoCSolution5::ReorderUpdate(vector<string> &Update)
{
    for (int32_t Index = 0; Index < Update.size(); Index++)
    {
        const auto& CurrentPage = Update[Index];
        vector<string> AfterUpdateList(Update.begin() + Index, Update.end());
        vector<string> BeforeUpdateList(Update.begin(), Update.begin() + Index);

        for (const auto& AfterUpdate : AfterDataCache[CurrentPage])
        {
            for (int32_t AfteUpdateListIndex = 0; AfteUpdateListIndex < AfterUpdateList.size(); AfteUpdateListIndex++)
            {
                if (AfterUpdate == AfterUpdateList[AfteUpdateListIndex])
                {
                    const auto ErasePosition = Index + AfteUpdateListIndex;
                    Update.erase(Update.begin() + ErasePosition);
                    const auto InsertPosition = Index == 0  ? Index : Index - 1;
                    Update.insert(Update.begin() + InsertPosition, AfterUpdate);
                    return ReorderUpdate(Update);
                }
            }
        }

        for (const auto& BeforeUpdate : BeforeDataCache[CurrentPage])
        {
            for (int32_t BeforeUpdateListIndex = 0; BeforeUpdateListIndex < BeforeUpdateList.size(); BeforeUpdateListIndex++)
            {
                if (BeforeUpdate == BeforeUpdateList[BeforeUpdateListIndex])
                {
                    const auto ErasePosition = BeforeUpdateListIndex;
                    Update.erase(Update.begin() + ErasePosition);
                    const auto InsertPosition = Index == Update.size() - 2  ? Index - 1  : Index;
                    Update.insert(Update.begin() + InsertPosition, BeforeUpdate);
                    return ReorderUpdate(Update);
                }
            }
        }
    }

}
