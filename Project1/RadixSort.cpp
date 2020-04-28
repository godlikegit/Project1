#include "inc.h"
#include "common.h"


int getDigit(int x, int d) {
    return ((x / ((int)pow(10, d - 1))) % 10);
}

void RadixSort() {
    const int radix = 10;
    const int digit = 4;
    const int L = 0;
    const int R = N-1;
    
    int help[N] = {};
    int i = 0, j = 0;
    for (int d = 1; d <= digit; ++d) {
        int count[radix] = {};
		for (i = L; i <= R; i++) {
			j = getDigit(arr[i], d);
			count[j]++;
		}
		for (i = 1; i < radix; i++) {
			count[i] = count[i] + count[i - 1];
		}
		for (i = R; i >= L; i--) {

			j = getDigit(arr[i], d);
			help[count[j] - 1] = arr[i];
			count[j]--;
		}
		for (i = L, j = 0; i <= R; i++, j++) {
			arr[i] = help[j];
		}
    }
}