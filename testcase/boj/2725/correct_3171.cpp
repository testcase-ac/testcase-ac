#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> ans(1001);
	for(int x=0; x<=1000; x++) {
		for(int y=0; y<=1000; y++) {
			int g = __gcd(x, y);
			if(g == 1)
				ans[max(x, y)]++;
		}
	}
	for(int i=2; i<=1000; i++) {
		ans[i] += ans[i-1];
	}
	while(n--) {
		int t;
		cin >> t;
		cout << ans[t] << '\n';
	}
}
