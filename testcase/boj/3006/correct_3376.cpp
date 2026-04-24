#include <bits/stdc++.h>
using namespace std;
inline int lsb(int i){return i&-i;}
const int MX = 100005;
int n;
struct BIT {
	int t[MX];
	void update(int i, int v) {
		while(i <= n) {
			t[i] += v;
			i += lsb(i);
		}
	}
	int query(int i) {
		int ret = 0;
		while(i) {
			ret += t[i];
			i -= lsb(i);
		}
		return ret;
	}
};
BIT bit;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	int inv[n+1];
	for(int i=1; i<=n; i++) {
		int t;
		cin >> t;
		inv[t] = i;
	}
	for(int i=1; i<=n; i++) {
		bit.update(i, 1);
	}
	int l = 1, r = n;
	while(l <= r) {
		int p = inv[l++];
		bit.update(p, -1);
		cout << bit.query(p) << '\n';
		if(l > r) break;
		p = inv[r--];
		bit.update(p, -1);
		cout << (r-l+1) - bit.query(p) << '\n';
	}
}
