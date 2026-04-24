#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 	3e5+2, INF = INT_MAX;
int po[MX];
tuple<int,int,int> qry[MX];
int seg[MX*2];
int n, m;
void update(int l, int r, int v) {
	l += m, r += m;
	while(l < r) {
		if(l&1) {
			seg[l] += v;
			seg[l] = min(seg[l], INF);
			l++;
		}
		if(r&1) {
			r--;
			seg[r] += v;
			seg[r] = min(seg[r], INF);
		}
		l /= 2;
		r /= 2;
	}
}
int query(int p) {
	int res = 0;
	p += m;
	while(p) {
		res += seg[p];
		p /= 2;
	}
	return res;
}
int l[MX], r[MX];
vector<int> pbs[MX], own[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int t;
		cin >> t;
		t--;
		own[t].push_back(i);
	}
	for(int i=0; i<n; i++) {
		cin >> po[i];
	}
	int q;
	cin >> q;
	for(int i=1; i<=q; i++) {
		auto& [a, b, c] = qry[i];
		cin >> a >> b >> c;
		a--;
		b--;
	}
	for(int i=0; i<n; i++) {
		l[i] = 1;
		r[i] = q+1;
	}
	while(1) {
		bool done = 1;
		memset(seg, 0, sizeof seg);
		for(int i=0; i<n; i++) {
			if(l[i] < r[i]) {
				int t = (l[i]+r[i])/2;
				pbs[t].push_back(i);
				done = 0;
			}
		}
		if(done) {
			for(int i=0; i<n; i++) {
				if(l[i] == q+1)
					cout << "NIE\n";
				else
					cout << l[i] << '\n';
			}
			return 0;
		}
		for(int i=1; i<=q; i++) {
			const auto& [lu, ru, au] = qry[i];
			if(lu <= ru) {
				update(lu, ru+1, au);
			} else {
				update(lu, m, au);
				update(0, ru+1, au);
			}
			for(int t: pbs[i]) {
				int sum = 0;
				for(int k: own[t])
					sum += query(k);
				if(sum >= po[t]) {
					r[t] = i;
				} else {
					l[t] = i+1;
				}
			}
			pbs[i].clear();
		}
	}
}
