#include <bits/stdc++.h>
using namespace std;
const int MX = 6e5+2;
int segt[MX*2], n;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	int sz = 1<<(32-__builtin_clz(n));
	for(int i=0; i<n; i++) {
		cin >> segt[sz+i];
	}
	for(int i=sz-1; i; i--) {
		segt[i] = segt[2*i]+segt[2*i+1];
	}
	int q;
	cin >> q;
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int a, b;
			cin >> a >> b;
			a += sz-1;
			while(a) {
				segt[a] += b;
				a /= 2;
			}
		} else {
			int x, p = 1;
			cin >> x;
			while(p < sz) {
				if(segt[2*p] >= x) {
					p = 2*p;
				} else {
					x -= segt[2*p];
					p = 2*p+1;
				}
			}
			cout << p-sz+1 << '\n';
		}
	}
}
