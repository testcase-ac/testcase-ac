#include <bits/stdc++.h>
using namespace std;
int cnt[12];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, s, r, t;
	cin >> n >> s >> r;
	for(int i=1; i<=n; i++) {
		cnt[i] = 1;
	}
	for(int i=0; i<s; i++) {
		cin >> t;
		cnt[t]--;
	}
	for(int i=0; i<r; i++) {
		cin >> t;
		cnt[t]++;
	}
	int ans = 0;
	for(int i=1; i<=n; i++) {
		if(!cnt[i]) {
			if(cnt[i-1] == 2)
				cnt[i] = 1;
			else if(cnt[i+1] == 2) {
				cnt[i] = 1;
				cnt[i+1] = 1;
			}
		}
		if(!cnt[i])
			ans++;
	}
	cout << ans;
}
