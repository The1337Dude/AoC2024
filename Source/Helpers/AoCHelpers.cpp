#include "AoCHelpers.h"
#include <filesystem>
#include <sstream>
#include <math.h>

using namespace std;

namespace AoCHelpers
{
    vector<string> ProcessInput(const int ProblemNumber)
    {
        string FilePath;
        FilePath = to_string(ProblemNumber) + ".txt";

        return ProcessInput(FilePath);
    }

    vector<string> ProcessInput(const string& Path)
    {
        vector<string> Result;
        string buffer;
        ifstream InputFile(Path);

        if (InputFile.is_open())
        {
            while (getline(InputFile, buffer))
            {
                Result.push_back(buffer);
            }
        }

        return Result;
    }

    vector<string> Tokenize(const string& InputString, const char& Token)
    {
        vector<string> Result;

        // stringstream class check1
        stringstream stream(InputString);

        string intermediate;

        // Tokenizing w.r.t. space Token
        while (getline(stream, intermediate, Token))
        {
            if(intermediate.empty())
            {
                continue;
            }
            
            Result.push_back(intermediate);
        }

        return Result;
    }

    float distance(int x1, int y1, int x2, int y2)
    {
        // Calculating distance
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
    }

    vector<int32_t> Convert(const vector<string>& InStringArray)
    {
        vector<int32_t> IntArray;
        for (const auto& StringItem : InStringArray)
        {
            IntArray.push_back(atoi(StringItem.data()));
        }

        return IntArray;
    }

    bool IsNumeric(const string &InString)
    {
        for (const auto& CharInString : InString)
        {
            if (!isdigit(CharInString))
            {
                return false;
            }
        }

        return true;
    }

    vector<PositionType> GetAdjacentPositions(const int MaxRow, const int MaxColumn, const PositionType& CurrentPosition)
    {
        const vector<PositionType> PositionModifiers = { {-1, -1}, {-1,0}, {-1,1}, {0, 1}, {1,1}, {1,0}, {1, -1}, {0,-1}};
        return GetRelativePositions(MaxRow, MaxColumn, CurrentPosition, PositionModifiers);
    }

    vector<PositionType> GetRelativePositions(const int MaxRow, const int MaxColumn, const PositionType& CurrentPosition, const vector<PositionType>& PositionModifiers)
    {
        vector<PositionType> RelativePositions;
        
        for(const auto& PositionModifier : PositionModifiers)
        {
            const PositionType AdjacentPosition = { CurrentPosition.first + PositionModifier.first, CurrentPosition.second + PositionModifier.second };
            if(AdjacentPosition.first >= 0 && AdjacentPosition.second >= 0 &&
               AdjacentPosition.second <= MaxColumn && AdjacentPosition.first <= MaxRow)
            {
                RelativePositions.push_back(AdjacentPosition);
            }
        }
        
        return RelativePositions;
    }

    bool IsOnBoundary(const int MaxRow, const int MaxColumn, const PositionType& CurrentPosition)
    {
        if(CurrentPosition.first == MaxRow || CurrentPosition.second == MaxColumn || CurrentPosition.first == 0 || CurrentPosition.second == 0)
        {
            return true;
        }
        
        return false;
    }
}
