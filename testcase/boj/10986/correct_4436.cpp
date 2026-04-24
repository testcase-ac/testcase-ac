#include <bits/stdc++.h>
using namespace std;

int cnt[1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cnt[0] = 1;
	int n, m, curr = 0;
	long long ans = 0;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		curr = (curr+t)%m;
		ans += cnt[curr];
		cnt[curr]++;
	}
	cout << ans;
}
