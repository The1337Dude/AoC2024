#include <iostream>
using namespace std;

#include "Solutions/AoCSolution1.h"
#include "Solutions/AoCSolution2.h"
#include "Solutions/AoCSolution3.h"
#include "Solutions/AoCSolution4.h"
#include "Solutions/AoCSolution5.h"
#include "Solutions/AoCSolution6.h"

int main()
{
    shared_ptr<IAocSolution> Solution = make_shared<AoCSolution6>();

    Solution->Initialize(AoCHelpers::ProcessInput(6));

    cout << Solution->GetResult(1) << endl;
    cout << Solution->GetResult(2) << endl;

    return 0;
}