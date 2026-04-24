#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 3e3+2;
bitset<3000> bs[MX], seen;
vector<int> adj[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
		bs[a][b] = bs[b][a] = 1;
	}
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		bs[i][i] = 1;
		v[i] = i;
	}
	sort(v.begin(), v.end(), [&](int i, int j){return adj[i].size() > adj[j].size();});
	for(int k: v) {
		seen.reset();
		seen[k] = 1;
		bitset<3000> cbs = bs[k];
		int T = n/3-1;
		while(T) {
			int mxv = -1, mxi = 0;
			for(int i=0; i<n; i++) {
				if(seen[i]) continue;
				bitset<3000> tmp = cbs & bs[i];
				if((tmp & seen) != seen) continue;
				int cnt = tmp.count();
				if(cnt > mxv) {
					mxv = cnt;
					mxi = i;
				}
			}
			cbs = cbs & bs[mxi];
			seen[mxi] = 1;
			if(!mxv)
				break;
			T--;
		}
		if(T)
			continue;
		for(int i=0; i<n; i++) {
			if(seen[i])
				cout << i+1 << ' ';
		}
		exit(0);
	}
}
