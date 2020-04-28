#pragma once

const int N = 5000;
const int MIN_VAL = 10000;
const int MAX_VAL = 30000;
extern int arr[N];
extern int arrCopy[N];

void randArray();
void copyArray();
void printArray(int* pArr);
bool checkArray(bool lessToMore = true);
bool isEqual();
void swap(int* p, int i, int j);

class StopWatch
{
public:
    StopWatch();
    void Reset();
    uint64_t Elapsed();
private:
    uint64_t m_start;
};

void SelectionSort();
void RadixSort();
