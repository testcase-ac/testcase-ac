#include <bits/stdc++.h>
using namespace std;
vector<int> mst[200000];
int n;
int count(vector<int>& v, int t) {
	return v.end() - upper_bound(v.begin(), v.end(), t);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		mst[n+i] = {t};
	}
	for(int t=n-1; t; t--) {
		vector<int> &v = mst[t], &vl = mst[2*t], &vr = mst[2*t+1];
		int i = 0, j = 0;
		while(i < vl.size() && j < vr.size()) {
			if(vl[i] < vr[j]) {
				v.push_back(vl[i++]);
			} else {
				v.push_back(vr[j++]);
			}
		}
		while(i < vl.size()) {
			v.push_back(vl[i++]);
		}
		while(j < vr.size()) {
			v.push_back(vr[j++]);
		}
	}
	int ans = 0, m;
	cin >> m;
	while(m--) {
		int tans = 0, a, b, c;
		cin >> a >> b >> c;
		a ^= ans;
		b ^= ans;
		c ^= ans;
		a--;
		a += n, b += n;
		while(a < b) {
			if(a&1) tans += count(mst[a++], c);
			if(b&1) tans += count(mst[--b], c);
			a /= 2, b /= 2;
		}
		ans = tans;
		cout << ans << '\n';
	}
}
