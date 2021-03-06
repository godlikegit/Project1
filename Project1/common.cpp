#include "inc.h"
#include "common.h"

int arr[N];
int arrCopy[N];

void randArray() {
    for (int i = 0; i < N; ++i) {
        arr[i] = Random::get(MIN_VAL, MAX_VAL);
    }
}

void copyArray() {
    for (int i = 0; i < N; ++i) {
        arrCopy[i] = arr[i];
    }
}

void printArray(int* pArr) {
    for (int i = 0; i < N; ++i) {
        cout << pArr[i] << ',';
        if (i > 0 && i % 10 == 0) cout << endl;
    }
    cout << endl;
}

bool checkArray(bool lessToMore) {
    if (lessToMore) {
        for (int i = 0; i < N - 1; ++i) {
            if (arr[i] > arr[i + 1]) return false;
        }
    }
    else {
        for (int i = 0; i < N - 1; ++i) {
            if (arr[i] < arr[i + 1]) return false;
        }
    }

    return true;
}

bool isEqual() {
    for (int i = 0; i < N; ++i) {
        if (arr[i] != arrCopy[i]) return false;
    }
    return true;
}

void swap(int* p, int i, int j)
{
    int tmp = p[i];
    p[i] = p[j];
    p[j] = tmp;
    //p[i] ^= p[j];
    //p[j] ^= p[i];
    //p[i] ^= p[j];
}