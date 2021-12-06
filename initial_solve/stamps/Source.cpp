/*
ID: ruifanl1
TASK: stamps
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int K, N;
vector<int> nums;
vector<int> stamps;

void sort(vector<int> s) {
	int len = s.size();
	for (int i = 0; i < len - 1; i++) {
		int a = stamps[i];
		for (int j = i + 1; j < len; j++) {
			int b = stamps[j];
			if (a < b) {
				stamps[i] = b;
				stamps[j] = a;
				a = b;
			}
		}
	}
}

bool checkCreatable(int val, int k) {
	int l = val - nums.size();
	for (int i = 0; i <= l; i++) {
		nums.push_back(-1);
	}

	int least = -1;
	bool creatable = false;
	for (int i = 0; i < stamps.size(); i++) {
		int newVal = val - stamps[i];
		if (newVal < 0) {
			continue;
		}
		if (newVal == 0) {
			nums[val] = 1;
			return true;
		}
		int num = nums[newVal] + 1;
		if (num > k) {
			continue;
		}
		if (num < least || least == -1) {
			least = num;
			creatable = true;
		}
	}
	if (creatable) {
		nums[val] = least;
	}
	return creatable;
}

int main() {
	ifstream fin("stamps.in");
	fin >> K >> N;
	stamps.resize(N);
	for (int i = 0; i < N; i++) {
		fin >> stamps[i];
	}
	
	int ans = 0, deleted = 0;
	sort(stamps);
	for (int i = 1; i <= K; i++) {
		while (checkCreatable(ans + 1 - deleted, i)) {
			ans++;
			if ((ans - 10001) % 10000 == 0 && ans > 10002) {
				deleted += 10000;
				nums.erase(nums.begin(), nums.begin() + 10000);
			}
		}
	}

	ofstream fout("stamps.out");
	fout << ans << '\n';
}