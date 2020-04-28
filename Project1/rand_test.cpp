#include "inc.h"
#include <windows.h>
#define RAND_MAX1 (RAND_MAX + 1)

//返回0~scale)的随机浮点数
float randFloat(float scale) {
    if (scale <= 0.0f) return 0.0f;
    return (float)rand() / float(RAND_MAX1) * scale;
}
//返回0~scale-1)的随机整数
int randInt(int scale) {
    if (scale <= 0 || scale > RAND_MAX1) return 0;
    return int((float)rand() / float(RAND_MAX1) * float(scale));
}

int randBig(int max)
{
    float rf = randFloat(1.0f);
    return int(rf * (max + 1));
}

int randBetween(int min, int max) {
    if (min == max) return min;
    else if (min > max) {
        min ^= max;
        max ^= min;
        min ^= max;
    }
    double r = (double)rand() * ((1.0 / (double)RAND_MAX + 1.0));
    r *= (double)max - (double)min + 1.0;
    return (int)(r + (double)min);
}

void fun3() {
    randBetween(INT_MIN, INT_MAX);
    srand((unsigned)time(nullptr));
    while (true) {
        while (true)
        {
            int i = randBetween(INT_MIN, INT_MAX);
            //int i = randBig(INT_MAX - 1);
           // if (10000 > i) {
            printf("%d,", i);
            //     break;
            // }
             //printf("%d,", i);
            Sleep(1000);
        }
        Sleep(1000);
    }
}