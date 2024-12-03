#include <iostream>
using namespace std;

#include "Solutions/AoCSolution1.h"

int main()
{
    shared_ptr<IAocSolution> Solution = make_shared<AoCSolution1>();

    Solution->Initialize(AoCHelpers::ProcessInput(1));

    cout << Solution->GetResult(1) << endl;
    cout << Solution->GetResult(2) << endl;

    return 0;
}