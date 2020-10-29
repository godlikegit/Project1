#include "inc.h"
#include "common.h"

#define UC unsigned char

template<typename T>
void Radixsort(T* fst, T* lst, T* buf, int* op) {
	static int b[0x100];
	int Len = lst - fst, Sz = sizeof(T), at = 0, i, j;
	UC* bgn, * end, tmp;
	for (i = 0; i < Sz; ++i) {
		if (op[i] == -1)continue;
		bgn = (UC*)fst + i; end = (UC*)lst + i;
		tmp = ((op[i] & 1) ? 0xff : 0) ^ ((op[i] & 2) ? 0x80 : 0);
		memset(b, 0, sizeof(b));
		for (UC* it = bgn; it != end; it += Sz)++b[tmp ^ *it];
		for (j = 1; j < 0x100; ++j)b[j] += b[j - 1];
		for (UC* it = end; it != bgn; buf[--b[tmp ^ *(it -= Sz)]] = *--lst);
		lst = buf + Len; swap(fst, buf); at ^= 1;
	}
	if (at)memcpy(buf, fst, Sz * Len);
}
 
void test4()
{
	int res[N];
	int op[] = { 0,0,0,2 };

	StopWatch sw0;
	int more5sec_count = 0;
	for (int i = 0; i < 1000; ++i) {
		randArray();
		StopWatch sw;
		Radixsort<int>(arr, arr + N, res, op);

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
}