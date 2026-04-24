#include <bits/stdc++.h>
using namespace std;
map<int,int> mp;
vector<pair<int, int>> v;
int n, m, w[8];
void f(int p) {
	if(p == n) {
		if(accumulate(w, w+8, 0) != m) return;
		for(int i=0; i<n; i++) {
			for(int j=0; j<w[i]; j++) {
				cout << v[i].first << ' ';
			}
		}
		cout << '\n';
		return;
	}
	for(int i=v[p].second; i>=0; i--) {
		w[p] = i;
		f(p+1);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		mp[t]++;
	}
	v = vector<pair<int, int>>(mp.begin(), mp.end());
	n = v.size();
	f(0);
}
