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

	//分数、排名、PID

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
		// 有多少个数准备多少个辅助空间
		RankItem help[N] = {};
		for (int d = 1; d <= digit; d++) { // 有多少位就进出几次
			// 10个空间
			// count[0] 当前位(d位)是0的数字有多少个
			// count[1] 当前位(d位)是(0和1)的数字有多少个
			// count[2] 当前位(d位)是(0、1和2)的数字有多少个
			// count[i] 当前位(d位)是(0~i)的数字有多少个
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

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x=0) : val(x), left(nullptr), right(nullptr) {}
};
bool isLeaf(TreeNode* node) {
	return node->left == nullptr
		&& node->right == nullptr;
}
int minDepth(TreeNode* root) {
	if (nullptr == root) return 0;
	if (isLeaf(root)) return 1;
	int left_dep = minDepth(root->left);
	int right_dep = minDepth(root->right);
	return 1 + (left_dep < right_dep ? left_dep : right_dep);
}

int main() {

	TreeNode a(1);
	TreeNode b(2);
	a.left = &b;
	int d = minDepth(&a);
    return 0;
}
//最少步数的方法: [n/2个2 + n%2个1]
//最大步数的方法: [0个2 + n个1]
