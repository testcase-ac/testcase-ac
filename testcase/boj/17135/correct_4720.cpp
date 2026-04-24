#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
int orig[15][15], arr[15][15], prm[15];
int dist(pii a, pii b) {
	return abs(a.first-b.first) + abs(a.second-b.second);
}
vector<pii> enemy;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, d;
	cin >> n >> m >> d;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			cin >> orig[i][j];
		}
	}
	prm[0] = prm[1] = prm[2] = 1;
	int ans = 0;
	do {
		memcpy(arr, orig, sizeof arr);
		int t = n, tans = 0;
		while(t--) {
			enemy.clear();
			for(int j=0; j<m; j++) {
				for(int i=0; i<n; i++) {
					if(arr[i][j])
						enemy.push_back({i,j});
				}
			}
			for(int i=0; i<m; i++) {
				if(!prm[i]) continue;
				int mnd = 100;
				pii mnp;
				for(auto pr: enemy) {
					if(dist(pr, {n, i}) < mnd) {
						mnd = dist(pr, {n, i});
						mnp = pr;
					} 
				}
				if(mnd == 100)
					goto end;
				if(mnd <= d && arr[mnp.first][mnp.second]) {
					arr[mnp.first][mnp.second] = 0;
					tans++;
				}
			}
			for(int i=n-1; i; i--)
				memcpy(arr[i], arr[i-1], sizeof arr[i]);
			memset(arr[0], 0, sizeof arr[0]);
		}
		end:;
		ans = max(tans, ans);
	} while(prev_permutation(prm, prm+m));
	cout << ans;
}
