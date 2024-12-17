#pragma once

#include <vector>
#include <set>

#include "Helpers/AoCHelpers.h"

class AoCSolution6 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;

private:
    char Rotate(const char& InChar);
    PositionType GetNextPositionDelta(const char& InChar);
    PositionType GetStartingPosition();
    int32_t GetNumGuardPositions();
    bool HasLoop(const vector<string>& InputDataWithObstacle);
    void DrawPath(const set<PositionType>& OccupiedPositions, const vector<string>& InputMap);

private:
    vector<string> InputData;
};