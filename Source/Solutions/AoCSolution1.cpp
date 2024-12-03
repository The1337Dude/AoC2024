#include "AoCSolution1.h"

#include <map>

using namespace std;

void AoCSolution1::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution1::GetResult(const int Part)
{
    const auto Lists = GetLists();
    if (Part == 1)
    {
        return to_string(GetDistanceBetweenLists(Lists));
    }
    else
    {
        return to_string(GetSimilarityBetweenLists(Lists));
    }
}

pair<vector<int32_t>, vector<int32_t>> AoCSolution1::GetLists() const
{
    vector<int32_t> List1;
    vector<int32_t> List2;

    for (const auto& InputLine : InputData)
    {
        const char Token = ' ';
        const auto Tokens = AoCHelpers::Tokenize(InputLine, Token);

        if (Tokens.size() < 2)
        {
            continue;
        }

        List1.push_back(atoi(Tokens[0].data()));
        List2.push_back(atoi(Tokens[1].data()));
    }

    return { move(List1), move(List2) };
}

void AoCSolution1::SortList(vector<int32_t>& List)
{
    sort(List.begin(), List.end());
}

int32_t AoCSolution1::GetDistanceBetweenLists(const pair<vector<int32_t>, vector<int32_t>>& InLists)
{
    auto Lists = InLists;
    int32_t Distance = 0;
    SortList(Lists.first);
    SortList(Lists.second);

    for (int32_t Index = 0; Index < Lists.first.size(); Index++)
    {
        Distance += abs(Lists.first[Index] - Lists.second[Index]);
    }

    return Distance;
}

int32_t AoCSolution1::GetSimilarityBetweenLists(const pair<vector<int32_t>, vector<int32_t>> &Lists)
{
    int32_t Similarity = 0;

    map<int32_t, int32_t> NumberOccurenceMap;

    for (const auto& Location : Lists.second)
    {
        NumberOccurenceMap[Location]++;
    }

    for (const auto& Location : Lists.first)
    {
        Similarity += Location * NumberOccurenceMap[Location];
    }

    return Similarity;
}

