#include <bits/stdc++.h>
using namespace std;
const int MX = 2e4+2;
int par[MX], dist[MX];
pair<int, int> f(int i) {
	if(i == par[i])
		return {i, 0};
	auto pr = f(par[i]);
	par[i] = pr.first;
	pr.second += dist[i];
	dist[i] = pr.second;
	return pr;
}
void solve() {
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		par[i] = i;
		dist[i] = 0;
	}
	while(1) {
		char c;
		cin >> c;
		if(c == 'O') return;
		if(c == 'E') {
			int i;
			cin >> i;
			f(i);
			cout << dist[i] << '\n';
		} else {
			int i, j;
			cin >> i >> j;
			par[i] = j;
			dist[i] = abs(j-i)%1000;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		solve();
}
