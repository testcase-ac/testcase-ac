#include <bits/stdc++.h>
using namespace std;

const int MX = 100000;
vector<int> pos[MX+1];
pair<int, int> ans[MX+1];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		for(int i=0; i<=MX; i++) pos[i].clear();
		int n;
		cin >> n;
		for(int i=0; i<n; i++) {
			int x, y;
			cin >> x >> y;
			pos[x].push_back(y);
		}
		int y = 0, cnt = 1;
		for(int i=0; i<=MX; i++) {
			if(pos[i].empty()) continue;
			sort(pos[i].begin(), pos[i].end());
			if(pos[i].back() == y) reverse(pos[i].begin(), pos[i].end());
			assert(pos[i].front() == y);
			for(int ty: pos[i])
				ans[cnt++] = {i,ty};
			y = pos[i].back();
		}
		int m;
		cin >> m;
		for(int i=0; i<m; i++) {
			int t;
			cin >> t;
			cout << ans[t].first << ' ' << ans[t].second << '\n';
		}
	}
}
