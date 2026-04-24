#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5e5+2;
int arr[MX], acc[MX], nxt[MX];
int calc(int l, int r) {
	if(nxt[l] == nxt[r])
		return (r-l+2)*(r-l+1)/2;
	int ret = 0;
	if(nxt[l] == nxt[l-1]) {
		int d = nxt[l] - l;
		ret = d*(d+1)/2;
		l = nxt[l];
	}
	return ret + acc[r] - acc[l-1];
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, q;
	cin >> n >> q;
	int add = 0;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		if(arr[i] >= arr[i-1]) {
			add++;
		} else {
			add = 1;
			int j = i-1;
			while(j > 0 && !nxt[j]) {
				nxt[j] = i;
				j--;
			}
		}
		acc[i] = acc[i-1] + add;
	}

	while(q--) {
		int L, R;
		cin >> L >> R;
		int l = L, r = R;
		while(l < r) {
			int m = (l+r)/2;
			int c1 = calc(L, m), c2 = calc(m, R);
			if(c1 >= c2) {
				r = m;
			} else {
				l = m+1;
			}
		}
		int ans = max(calc(L, l), calc(l, R));
		if(l > L) {
			ans = min(ans, max(calc(L, l-1), calc(l-1, R)));
		}
		if(l < R) {
			ans = min(ans, max(calc(L, l+1), calc(l+1, R)));
		}
		cout << ans << '\n';
	}
}
