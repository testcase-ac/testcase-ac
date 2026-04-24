#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
int par[MX], diff[MX], sz[MX];
vector<int> buk[MX];
void solve() {
	int n, m;
	cin >> n >> m;
	if(!n)
		exit(0);
	for(int i=1; i<=n; i++) {
		par[i] = i;
		diff[i] = 0;
		buk[i] = {i};
		sz[i] = 1;
		buk[i].shrink_to_fit();
	}
	while(m--) {
		char c;
		cin >> c;
		if(c == '!') {
			int a, b, w;
			cin >> a >> b >> w;
			//printf("input: '! %d %d %d'\n", a, b, w);
			if(par[a] != par[b]) {
				w = w - diff[b] + diff[a];
				a = par[a], b = par[b];

				if(sz[a] < sz[b]) {
					swap(a, b);
					w *= -1;
				}
				for(int t: buk[b]) {
					assert(par[t] == b);
					par[t] = a;
					diff[t] += w;
				}
				sz[a] += sz[b];
				if(sz[a] > n/2) {
					buk[a].clear();
					buk[b].clear();
					buk[a].shrink_to_fit();
					buk[b].shrink_to_fit();
				} else {
					buk[a].insert(buk[a].end(), buk[b].begin(), buk[b].end());
				}
			}
		} else {
			int a, b;
			cin >> a >> b;
			//printf("input: '? %d %d'\n", a, b);
			if(par[a] == par[b]) {
				cout << diff[b] - diff[a] << '\n';
			} else {
				cout << "UNKNOWN\n";
			}
		}
	}

}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		solve();
	}
}
