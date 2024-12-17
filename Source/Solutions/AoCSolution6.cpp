#include "AoCSolution6.h"

#include <set>
#include <map>

void AoCSolution6::Initialize(const vector<string> &Input)
{
    InputData = Input;
}

string AoCSolution6::GetResult(const int Part)
{
    if (Part == 1)
    {
        return to_string(GetNumGuardPositions());
    }
    else
    {

        int32_t Result = 0;
        for (int32_t Row = 0; Row < InputData.size(); Row++)
        {
            for (int32_t Column = 0; Column < InputData[Row].size(); Column++)
            {
                if (InputData[Row][Column] == '.')
                {
                    auto InputWithObstacles = InputData;
                    InputWithObstacles[Row][Column] = 'O';
                    Result += HasLoop(InputWithObstacles);
                }
            }
        }
        return to_string(Result);
    }
}

char AoCSolution6::Rotate(const char& InChar)
{
    switch (InChar)
    {
        case '^':
            return '>';
        case '>':
            return 'v';
        case 'v':
            return '<';
        case '<':
            return '^';
    }

    return '^';
}

PositionType AoCSolution6::GetNextPositionDelta(const char& InChar)
{
    switch (InChar)
    {
        case '^':
            return { -1, 0};
        case '>':
            return {0, 1};
        case 'v':
            return {1 , 0};
        case '<':
            return {0, -1};
    }

    return {-1, 0};
}

PositionType AoCSolution6::GetStartingPosition()
{
    for (int32_t Row = 0; Row < InputData.size(); Row++)
    {
        for (int32_t Column = 0; Column < InputData[Row].size(); Column++)
        {
            if (InputData[Row][Column] == '^')
            {
                return {Row, Column};
            }
        }
    }

    return {0,0};
}

int32_t AoCSolution6::GetNumGuardPositions()
{
    const static auto MaxRow = InputData.size() - 1;
    const static auto MaxColumn = InputData.empty() ? 0 : InputData[0].size();

    PositionType CurrentPosition = GetStartingPosition();
    char CurrentDirection = '^';
    set<PositionType> OccupiedPositions = { GetStartingPosition() };
    do
    {
        // Update Position Based on what's next
        const auto NextPositionDelta = GetNextPositionDelta(CurrentDirection);
        const PositionType NextPosition = { CurrentPosition.first + NextPositionDelta.first , CurrentPosition.second + NextPositionDelta.second};
        if (NextPosition.first > MaxRow || NextPosition.second > MaxColumn || NextPosition.first < 0 || NextPosition.second < 0)
        {
            break;
        }

        if (InputData[NextPosition.first][NextPosition.second] == '#')
        {
            CurrentDirection = Rotate(CurrentDirection);
            continue;
        }

        CurrentPosition = NextPosition;
        OccupiedPositions.insert(CurrentPosition);
    } while (true);

    cout << endl;
    return OccupiedPositions.size();
}

bool AoCSolution6::HasLoop(const vector<string>& InputDataWithObstacle)
{
    const static auto MaxRow = InputDataWithObstacle.size() - 1;
    const static auto MaxColumn = InputDataWithObstacle.empty() ? 0 : InputDataWithObstacle[0].size();

    PositionType CurrentPosition = GetStartingPosition();
    char CurrentDirection = '^';
    map<PositionType, char> OccupiedPositions = {{CurrentPosition, CurrentDirection}};
    do
    {
        // Update Position Based on what's next
        const auto NextPositionDelta = GetNextPositionDelta(CurrentDirection);
        const PositionType NextPosition = { CurrentPosition.first + NextPositionDelta.first , CurrentPosition.second + NextPositionDelta.second};
        if (NextPosition.first > MaxRow || NextPosition.second > MaxColumn || NextPosition.first < 0 || NextPosition.second < 0)
        {
            break;
        }

        if (InputDataWithObstacle[NextPosition.first][NextPosition.second] == '#' || InputDataWithObstacle[NextPosition.first][NextPosition.second] == 'O')
        {
            CurrentDirection = Rotate(CurrentDirection);
            continue;
        }

        CurrentPosition = NextPosition;
        if (OccupiedPositions.contains(CurrentPosition) && OccupiedPositions[CurrentPosition] == CurrentDirection)
        {
            return true;
        }

        OccupiedPositions.insert({CurrentPosition, CurrentDirection});
    } while (true);

    return false;
}

void AoCSolution6::DrawPath(const set<PositionType>& OccupiedPositions, const vector<string>& InputMap)
{
    for (int32_t RowIndex = 0; RowIndex < InputMap.size(); RowIndex++)
    {
        for (int32_t ColumnIndex = 0; ColumnIndex < InputMap[RowIndex].size(); ColumnIndex++)
        {
            if (OccupiedPositions.contains({RowIndex, ColumnIndex}))
            {
                cout << "x ";
            }
            else
            {
                cout << InputMap[RowIndex][ColumnIndex] << " ";
            }
        }

        cout << endl;
    }
}


