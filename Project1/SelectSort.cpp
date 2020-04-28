#include "inc.h"
#include "common.h"

void SelectionSort() {
    if (N < 2) return;

    for (int i = 0; i < N - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < N; ++j) {
            minIndex = arr[j] < arr[minIndex] ? j : minIndex;
        }
        swap(arr, i, minIndex);
    }
}