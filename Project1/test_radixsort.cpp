#include "inc.h"
#include "common.h"

extern void RadixSort();

void test3() {

    StopWatch sw0;
    int more5sec_count = 0;
    for (int i = 0; i < 1000; ++i) {
        randArray();
        StopWatch sw;
        //std::sort(arr, arr + N);
        RadixSort();
        auto used = sw.Elapsed();
        if (used > 4) ++more5sec_count;// cout << "used time {" << used << "}" << endl;
        //if (i == 100) printArray(arr);
        if (!checkArray(arr)) {
            cout << "not soted!" << endl;
            printArray(arr);
            return;
        }
    }
    cout << "soted!" << endl;
    cout << ">5ms has" << more5sec_count << endl;
    cout << "used time {" << sw0.Elapsed() << "}" << endl;
   // randArray();
   //
   // if (!checkArray(arr)) cout << "not soted!" << endl;
   // RadixSort();
   // cout << (checkArray(arr) ? "soted!" : "not soted!");
   //
   // printArray(arr);
}