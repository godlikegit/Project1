#include "inc.h"
#include "common.h"

void test1()
{
    randArray();

    if (!checkArray(arr)) cout << "not soted!" << endl;
    SelectionSort();
    cout << (checkArray(arr) ? "soted!" : "not soted!");

    printArray(arr);
}