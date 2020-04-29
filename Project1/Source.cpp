#include "inc.h"
#include <Windows.h>

const int TEST_COUNT = 1;
const int N = 5000;
const int WORNING_TIME = 8;

const int MIN_VAL = 100;
const int MAX_VAL = 999;

struct WatchTime {
	WatchTime() {
		stamp = chrono::steady_clock::now();
	}
	void Reset() {
		stamp = chrono::steady_clock::now();
	}
	uint64_t UsedTime() {
		auto now = chrono::steady_clock::now();
		return (uint64_t)(chrono::duration<double, milli>(now - stamp).count());
	}
	void CheckTime(int worring_time) {
		auto now = chrono::steady_clock::now();
		auto escape = (uint64_t)(chrono::duration<double, milli>(now - stamp).count());
		if (escape > worring_time) cout << "used time:" << escape << "ms" << endl;
	}
	chrono::steady_clock::time_point stamp;
};

struct Rank {

	//������������PID

	using PID = int;
	using RankItem = pair<int, PID>;
	using RankMap  = unordered_map<PID, int>;

	RankItem arr[N];
	RankMap rank;

	void randArray() {
		rank.clear();
		for (int i = 0; i < N; ++i) {
			arr[i].first = Random::get(MIN_VAL, MAX_VAL);
			arr[i].second = Random::get(MIN_VAL, MAX_VAL);
			rank[arr[i].second] = arr[i].first;
		}
	}
	bool checkArray() {
		for (int i = 0; i < N - 1; ++i) {
			if (arr[i].first > arr[i + 1].first) return false;
		}
		return true;
	}
	void printArray() {
		for (int i = 0; i < N; ++i) {
			cout << arr[i].first << "," << arr[i].second << " ";
		}
		cout << endl;
	}

	void printMap() {
		for (RankMap::const_iterator itr = rank.begin();
			itr != rank.end(); ++itr) {
			cout << itr->first << "," << itr->second << " ";
		}
		cout << endl;
	}

	int getDigit(int x, int d) {
		return ((x / ((int)pow(10, d - 1))) % 10);
	}
	int maxbits() {
		int _max = INT_MIN;
		for (int i = 0; i < N; i++) {
			_max = max(_max, arr[i].first);
		}
		int res = 0;
		while (_max != 0) {
			res++;
			_max /= 10;
		}
		return res;
	}
	void radixSort(int L, int R, int digit) {
		const int radix = 10;
		int i = 0, j = 0;
		// �ж��ٸ���׼�����ٸ������ռ�
		RankItem help[N] = {};
		for (int d = 1; d <= digit; d++) { // �ж���λ�ͽ�������
			// 10���ռ�
			// count[0] ��ǰλ(dλ)��0�������ж��ٸ�
			// count[1] ��ǰλ(dλ)��(0��1)�������ж��ٸ�
			// count[2] ��ǰλ(dλ)��(0��1��2)�������ж��ٸ�
			// count[i] ��ǰλ(dλ)��(0~i)�������ж��ٸ�
			int count[radix] = {};
			for (i = L; i <= R; i++) {
				j = getDigit(arr[i].first, d);
				count[j]++;
			}
			for (i = 1; i < radix; i++) {
				count[i] = count[i] + count[i - 1];
			}
			for (i = R; i >= L; i--) {
				j = getDigit(arr[i].first, d);
				//help[count[j] - 1].first = arr[i].first;
				help[count[j] - 1] = arr[i];
				count[j]--;
			}
			for (i = L, j = 0; i <= R; i++, j++) {
				arr[i] = help[j];
			}
		}
	}

	void test() {

		WatchTime wt0;
		WatchTime wt;
		while (1)
		{
			wt0.Reset();

			for (int i = 0; i < TEST_COUNT; ++i) {
				randArray();
				
				//printArray();
				//printMap();

				wt.Reset();
				radixSort(0, N - 1, maxbits());

				for (int r = 0; r < N; ++r) {
					rank[arr[r].second] = r;
				}
				wt.CheckTime(WORNING_TIME);

				if (!checkArray()) {
					cout << "not sorted!" << endl;
					break;
				}

				//cout << endl;
				//printArray();
				//printMap();
				//cout << endl;
			}
			cout << "sorted!" << endl;
			cout << "total used time = " << wt0.UsedTime() << "ms" << endl;
			cout << "average used time = " << wt0.UsedTime() / TEST_COUNT << "ms" << endl;

			
			Sleep(1000);
			//system("pause");
		}
	}
};


int main() {

	Rank r;
	r.test();
  
    return 0;
}