
#include "AoCSolution4.h"

#include <atomic>
#include <fenv.h>
#include <map>

// namespace AoCSolution4Helpers
// {
//     map<char, char> NextCharCache = {
//         {'X', 'M'},
//         {'M', 'A'},
//         {'A', 'S'}
//     };
// }

void AoCSolution4::Initialize(const vector<string> &Input)
{
    InputData = Input;
}

string AoCSolution4::GetResult(const int Part)
{
    const static auto MaxRow = InputData.size() - 1;
    const static auto MaxColumn = InputData.empty() ? 0 : InputData[0].size();

    const auto AreDiagonalCharactersMAndS = [this](const vector<PositionType>& Positions)
    {
        vector<char> ComparisionArray = {'M', 'S'};
        vector<char> DiagonalCharacters;
        for (const auto& Position : Positions)
        {
            DiagonalCharacters.push_back(InputData[Position.first][Position.second]);
        }
        sort(DiagonalCharacters.begin(), DiagonalCharacters.end());

        return DiagonalCharacters == ComparisionArray;
    };

    int32_t Result = 0;
    for (int32_t Row = 0; Row < InputData.size(); Row++)
    {
        for (int32_t Column = 0; Column < InputData.size(); Column++)
        {
            // cout << Row << "," << Column << endl;

            if (Part == 1)
            {
                for (const auto& SearchString : GetSearchStringsFromPosition(Row, Column))
                {
                    Result += SearchString.substr(0, 4) == "XMAS";
                }
                continue;
            }

            if (Part == 2)
            {
                if (InputData[Row][Column] != 'A')
                {
                    continue;
                }

                const auto DiagonalOnePositions = AoCHelpers::GetRelativePositions(MaxRow, MaxColumn, { Row, Column}, {{-1, -1}, {1,1}});
                const auto DiagonalTwoPositions = AoCHelpers::GetRelativePositions(MaxRow, MaxColumn, { Row, Column}, {{-1, 1}, {1,-1}});

                Result += (AreDiagonalCharactersMAndS(DiagonalOnePositions) && AreDiagonalCharactersMAndS(DiagonalTwoPositions));
                continue;
            }

            // cout << "----------------" << endl;
        }
    }

    return to_string(Result);
}

vector<string> AoCSolution4::GetSearchStringsFromPosition(const int32_t Row, const int32_t Column)
{
    if (Row < 0 || Row >= InputData.size() || Column < 0 || Column > InputData[Row].size() || InputData[Row][Column] != 'X')
    {
        return {};
    }

    vector<string> SearchStrings;
    // Horizontal
    auto Horizontal = InputData[Row].substr(Column);
    SearchStrings.push_back(move(Horizontal));
    // cout << "Horizontal: " << SearchStrings.back() << endl;

    // Reverse Horizontal
    auto ReverseHorizontal = InputData[Row].substr(0, Column + 1);
    reverse(ReverseHorizontal.begin(), ReverseHorizontal.end());
    SearchStrings.push_back(move(ReverseHorizontal));
    // cout << "Reverse Horizontal: " << SearchStrings.back() << endl;

    // Vertical
    string VerticalDown;
    for (int32_t Index = Row; Index < InputData.size(); Index++)
    {
        VerticalDown += InputData[Index][Column];
    }
    SearchStrings.push_back(move(VerticalDown));
    // cout << "Vertical Down: " << SearchStrings.back() << endl;

    // Vertical Up
    string VerticalUp;
    for (int32_t Index = Row; Index >= 0; Index--)
    {
        VerticalUp += InputData[Index][Column];
    }
    SearchStrings.push_back(move(VerticalUp));
    // cout << "Vertical Up: " << SearchStrings.back() << endl;

    // Diagonal Bottom Right
    string DiagonalBottomRight;
    int32_t RowIndex = Row;
    int32_t ColumnIndex = Column;
    while (RowIndex < InputData.size() && ColumnIndex < InputData[RowIndex].size())
    {
        DiagonalBottomRight += InputData[RowIndex][ColumnIndex];
        RowIndex++;
        ColumnIndex++;
    }
    SearchStrings.push_back(move(DiagonalBottomRight));
    // cout << "Diagonal Bottom Right: " << SearchStrings.back() << endl;

    // Diagonal Top Left
    string DiagonalTopLeft;
    RowIndex = Row;
    ColumnIndex = Column;
    while (RowIndex >= 0 && ColumnIndex >= 0)
    {
        DiagonalTopLeft += InputData[RowIndex][ColumnIndex];
        RowIndex--;
        ColumnIndex--;
    }
    SearchStrings.push_back(move(DiagonalTopLeft));
    // cout << "Diagonal Top Left: " << SearchStrings.back() << endl;

    // Diagonal Top Right
    string DiagonalTopRight;
    RowIndex = Row;
    ColumnIndex = Column;
    while (RowIndex >= 0 && ColumnIndex < InputData[RowIndex].size())
    {
        DiagonalTopRight += InputData[RowIndex][ColumnIndex];
        RowIndex--;
        ColumnIndex++;
    }
    SearchStrings.push_back(move(DiagonalTopRight));
    // cout << "Diagonal Top Right: " << SearchStrings.back() << endl;

    // Diagonal Bottom Left
    string DiagonalBottomLeft;
    RowIndex = Row;
    ColumnIndex = Column;
    while (RowIndex < InputData.size() && ColumnIndex >= 0)
    {
        DiagonalBottomLeft += InputData[RowIndex][ColumnIndex];
        RowIndex++;
        ColumnIndex--;
    }
    SearchStrings.push_back(move(DiagonalBottomLeft));
    // cout << "Diagonal Bottom Left: " << SearchStrings.back() << endl;

    return SearchStrings;
}

// bool AoCSolution4::DFS(const int32_t Row, const int32_t Column, const string& Prefix) const
// {
//     const static auto MaxRow = InputData.size() - 1;
//     const static auto MaxColumn = InputData.empty() ? 0 : InputData[0].size();
//
//     if (Prefix == "XMAS")
//     {
//         return true;
//     }
//
//     if (Row < 0 || Row >= InputData.size() || Column < 0 || Column > InputData[Row].size())
//     {
//         return false;
//     }
//
//     const char TargetChar = Prefix.empty() ? 'X' : AoCSolution4Helpers::NextCharCache[Prefix[Prefix.size() - 1]];
//     if (InputData[Row][Column] != TargetChar)
//     {
//         return false;
//     }
//
//     bool bHasNextChar = false;
//     for (const auto& AdjacentPosition : AoCHelpers::GetAdjacentPositions(MaxRow, MaxColumn, {Row, Column}))
//     {
//         bHasNextChar |= DFS(AdjacentPosition.first, AdjacentPosition.second, Prefix + TargetChar);
//     }
//
//     return bHasNextChar;
// }
