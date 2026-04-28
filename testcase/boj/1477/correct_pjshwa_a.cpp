#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int num, add, maxi, val;
vector<int> v;

bool start(int dist) {
	int cnt = 0;
	for (int i = 0; i < v.size() - 1; i++) {
		int d = v[i + 1] - v[i];
		int val;
		if (d / dist > 0) {
			if (d%dist == 0)	val = (d / dist) - 1;
			else val = (d / dist);
			cnt += val;
		}
	}
	if (cnt <= add) return true;
	return false;
}

int main() {
	cin >> num >> add >> maxi;
	v.push_back(0);
	for (int i = 0; i < num; i++) {
		cin >> val;
		v.push_back(val);
	}
	v.push_back(maxi);
	sort(v.begin(), v.end());
	int low = 0, high = maxi, mid, result;
	while (low<=high) {
		mid = low + (high - low) / 2;
		if (start(mid)) {
			high = mid - 1;
			result = mid;
		}
		else	low = mid + 1;
	}
	cout << result;
	return 0;
}
