#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6+1;
typedef long long ll;
inline int lsb(int i){return i&-i;}
ll bit[MX];
int n, m, arr[MX];
void update(int i, int v) {
	while(i <= n) {
		bit[i] += v;
		i += lsb(i);
	}
}
ll query(int i) {
	ll r = 0;
	while(i) {
		r += bit[i];
		i -= lsb(i);
	}
	return r;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		if(a) {
			update(b, c-arr[b]);
			arr[b] = c;
		} else {
			if(b > c) swap(b,c);
			cout << (query(c) - query(b-1)) << '\n';
		}
	}
}
