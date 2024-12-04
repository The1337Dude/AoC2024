#include <iostream>
using namespace std;

#include "Solutions/AoCSolution1.h"
#include "Solutions/AoCSolution2.h"

int main()
{
    shared_ptr<IAocSolution> Solution = make_shared<AoCSolution2>();

    Solution->Initialize(AoCHelpers::ProcessInput(2));

    cout << Solution->GetResult(1) << endl;
    cout << Solution->GetResult(2) << endl;

    return 0;
}