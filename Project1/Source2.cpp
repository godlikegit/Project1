#include "inc.h"
#include <windows.h>

uint32_t ron()
{
    static uint32_t x = 10, y = 18, z = 99, w = 0;
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}

void fun2()
{
    while (true) {
        std::cout << ron() << ",";
        Sleep(1000);
    }
    return;
    for (int i = 0; i < 10; ++i) {
        int n = 1000000;
        int arr[2] = { 0, 0 };
        while (true) {
            auto val = Random::get(1, 2);
            arr[val - 1]++;
            //std::cout << val<< ",";
            //Sleep(1000);
            if (n-- == 0)break;
        }
        std::cout << arr[0] << ", " << arr[1];
        std::cout << std::endl;

    }
}