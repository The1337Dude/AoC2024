#include "AoCSolution3.h"

#include <stack>

void AoCSolution3::Initialize(const vector<string>& Input)
{
    InputData = Input;
}

string AoCSolution3::GetResult(const int Part)
{
    int32_t OperationValues = 0;
    stack<EOperationType> PrefixStack;
    for (const auto& ProgramString : InputData)
    {
        pair<EOperationType, int32_t> Operation = { EOperationType::None, -1 };
        do
        {
            Operation = GetOperation(ProgramString, ++Operation.second);
            switch (Operation.first)
            {
                case EOperationType::None:
                    continue;
                    break;
                case EOperationType::Do:
                case EOperationType::Dont:
                {
                    PrefixStack.push(Operation.first);
                    continue;
                    break;
                }
                case EOperationType::Mult:
                    break;
            }

            if (Operation.first == EOperationType::Mult)
            {
                if (Part == 2)
                {
                    if (!PrefixStack.empty() && PrefixStack.top() == EOperationType::Dont)
                    {
                        continue;
                    }
                }

                OperationValues += GetOperationValue(ProgramString.substr(Operation.second));
            }

        }while (Operation.first != EOperationType::None && Operation.second != string::npos && Operation.second < ProgramString.size());
    }

    return to_string(OperationValues);
}

pair<EOperationType, int32_t> AoCSolution3::GetOperation(const string& OperationString, const int32_t Pos) const
{
    vector<pair<EOperationType, int32_t>> IndexesToCompare;

    const auto MultOperationIndex = OperationString.find("mul(", Pos);
    if (MultOperationIndex != string::npos)
    {
        IndexesToCompare.push_back({ EOperationType::Mult, MultOperationIndex});
    }

    const auto DoOperationIndex = OperationString.find("do()", Pos);
    if (DoOperationIndex != string::npos)
    {
        IndexesToCompare.push_back({ EOperationType::Do, DoOperationIndex});
    }

    const auto DontOperationIndex = OperationString.find("don't()", Pos);
    if (DontOperationIndex != string::npos)
    {
        IndexesToCompare.push_back({ EOperationType::Dont, DontOperationIndex});
    }

    if (IndexesToCompare.empty())
    {
        return { EOperationType::None, string::npos};
    }

    sort(IndexesToCompare.begin(), IndexesToCompare.end(),
        [](const pair<EOperationType, int32_t>& A, const pair<EOperationType, int32_t>& B)
    {
        return A.second < B.second;
    });

    return IndexesToCompare[0];
}

int32_t AoCSolution3::GetOperationValue(const string& OperationString) const
{
    const int32_t SeperatorIndex = OperationString.find(',');
    if (SeperatorIndex == string::npos)
    {
        return 0;
    }

    const auto Operand1String = OperationString.substr(4, SeperatorIndex - 4);
    if (!AoCHelpers::IsNumeric(Operand1String))
    {
        return 0;
    }
    int32_t Operand1 = atoi(Operand1String.data());

    int32_t BracketCloseIndex = OperationString.find(')');
    if (BracketCloseIndex == string::npos)
    {
        return 0;
    }

    const auto Operand2String = OperationString.substr(SeperatorIndex + 1, BracketCloseIndex - (SeperatorIndex + 1));
    if (!AoCHelpers::IsNumeric(Operand2String))
    {
        return 0;
    }
    int32_t Operand2 = atoi(Operand2String.data());

    return Operand1 * Operand2;
}

int32_t AoCSolution3::GetPrefixStringIndex(const string &PrefixString) const
{
    const auto DontPrefixStringIndex = PrefixString.find("don't()");
    return DontPrefixStringIndex;
}

bool AoCSolution3::GetPrefixStringValue(const string& PrefixString) const
{
    const auto DontPrefixStringIndex = PrefixString.find("don't()");
    return DontPrefixStringIndex != string::npos ? false : true;
}

