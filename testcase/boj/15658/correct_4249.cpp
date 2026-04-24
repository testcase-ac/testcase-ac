#include <bits/stdc++.h>
using namespace std;
int a[11], cnt[4], mx = INT_MIN, mn = INT_MAX, n;
void f(int t, int cur) {
	if(t == n) {
		mx = max(mx, cur);
		mn = min(mn, cur);
		return;
	}
	for(int i=0; i<4; i++) {
		if(cnt[i]) {
			cnt[i]--;
			if(i == 0) {
				f(t+1, cur+a[t]);
			} else if(i == 1) {
				f(t+1, cur-a[t]);
			} else if(i == 2) {
				f(t+1, cur*a[t]);
			} else {
				f(t+1, cur/a[t]);
			}
			cnt[i]++;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<4; i++) {
		cin >> cnt[i];
	}
	f(1, a[0]);
	cout << mx << '\n' << mn;
}
