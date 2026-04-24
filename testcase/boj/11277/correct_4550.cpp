#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<pair<int, int>> arr(k);
	for(int i=0; i<k; i++) {
		cin >> arr[i].first >> arr[i].second;
	}
	auto chk = [&](int x, int bm) {
		if(x > 0) {
			x--;
			return !!(bm&(1<<x));
		} else {
			x = abs(x)-1;
			return !(bm&(1<<x));
		}
	};
	for(int i=0; i<(1<<n); i++) {
		bool ok = 1;
		for(auto pr: arr) {
			if(!chk(pr.first, i) && !chk(pr.second, i)) {
				ok = 0;
				break;
			}
		}
		if(ok)
			return !(cout << 1);
	}
	cout << 0;
}
