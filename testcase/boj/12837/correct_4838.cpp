#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MX = 1e6+1;
ll bit[MX];
int lsb(int i) {return i&(-i);}
void upd(int i, int v) {
	while(i <= MX) {
		bit[i] += v;
		i += lsb(i);
	}
}
ll qry(int i) {
	ll r = 0;
	while(i) {
		r += bit[i];
		i -= lsb(i);
	}
	return r;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, q;
	cin >> n >> q;
	while(q--) {
		int a, b, c;
		cin >> a >> b >> c;
		if(a == 1) {
			upd(b, c);
		} else {
			cout << (qry(c) - qry(b-1)) << '\n';
		}
	}
}
