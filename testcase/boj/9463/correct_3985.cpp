#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
int n, bit[MX], a[MX], rev[MX];
inline int lsb(int i){return i&-i;}
void upd(int i, int v) {
	while(i <= n) {
		bit[i] += v;
		i += lsb(i);
	}
}
int qry(int i) {
	int r = 0;
	while(i) {
		r += bit[i];
		i -= lsb(i);
	}
	return r;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		cin >> n;
		for(int i=1; i<=n; i++)
			cin >> a[i];
		for(int i=1; i<=n; i++) {
			int t;
			cin >> t;
			rev[t] = i;
		}
		long long ans = 0;
		for(int i=n; i; i--) {
			ans += qry(rev[a[i]]);
			upd(rev[a[i]], 1);
		}
		memset(bit+1, 0, sizeof(int)*(n+1));
		cout << ans << '\n';
	}
}
