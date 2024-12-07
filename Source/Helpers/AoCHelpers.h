#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;
typedef pair<int, int> PositionType;

struct PositionTypeHasher
{
    size_t operator() (const PositionType& Key) const
    {
        return hash<int>()(Key.first) ^ hash<int>()(Key.second);
    }
};

struct PositionTypeComparator
{
    bool operator() (const PositionType& A, const PositionType& B) const
    {
        return A.first == B.first && A.second == B.second;
    }
};

namespace AoCHelpers
{
    vector<string> ProcessInput(const int ProblemNumber);
    vector<string> ProcessInput(const string& Path);
    vector<string> Tokenize(const string& InputString, const char& Token);
    float distance(int x1, int y1, int x2, int y2);
    float distance(int x1, int y1, int x2, int y2);
    vector<int32_t> Convert(const vector<string>& InStringArray);
    bool IsNumeric(const string& InString);

    template<typename T>
    void LogList(const vector<T>& List)
    {
        for(const auto& ListElement : List)
        {
            cout << ListElement << " ";
        }
        
        cout << endl;
    }

    vector<PositionType> GetAdjacentPositions(const int MaxRow, const int MaxColumn, const PositionType& CurrentPosition);
    vector<PositionType> GetRelativePositions(const int MaxRow, const int MaxColumn, const PositionType& CurrentPosition, const vector<PositionType>& PositionModifiers);
    bool IsOnBoundary(const int MaxRow, const int MaxColumn, const PositionType& CurrentPosition);
}

class IAocSolution
{
public:
    virtual void Initialize(const vector<string>& Input) = 0;
    virtual string GetResult(const int Part) = 0;
};
