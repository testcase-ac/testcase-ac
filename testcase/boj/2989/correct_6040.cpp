#include <bits/stdc++.h>
using namespace std;
const int MXX = 1e5+3, MXN = 3e5+3;
struct Pt{int x, y, f;};
Pt arr[MXN];
int ymax[MXX], par[MXN], dp[MXN];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k, sx, sy, gx, gy;
	cin >> n >> k;
	for(int i=0; i<n; i++) {
		cin >> arr[i].x >> arr[i].y >> arr[i].f;
	}
	sx = arr[0].x, sy = arr[0].y;
	gx = arr[n-1].x, gy = arr[n-1].y;
	sort(arr, arr+n, [](Pt &a, Pt &b){return tie(a.x, a.y) < tie(b.x, b.y);});
	memset(par, -1, sizeof par);
	memset(ymax, -1, sizeof ymax);
	memset(dp, -1, sizeof dp);
	int xmax = -1;
	bool start = 0;
	for(int i=0; i<n; i++) {
		if(arr[i].x == sx && arr[i].y == sy) {
			dp[i] = arr[i].f;
			start = 1;
		}
		if(!start) continue;
		if(i && arr[i].x != arr[i-1].x)
			xmax = -1;
		if(xmax != -1 && dp[xmax] >= k) {
			dp[i] = dp[xmax]-k+arr[i].f;
			par[i] = xmax;
		}
		int &ymi = ymax[arr[i].y];
		if(ymi != -1 && dp[ymi] >= k && dp[ymi]-k+arr[i].f > dp[i]) {
			dp[i] = dp[ymi]-k+arr[i].f;
			par[i] = ymi;
		}
		if(xmax == -1 || dp[i] > dp[xmax])
			xmax = i;
		if(ymi == -1 || dp[i] > dp[ymi])
			ymi = i;
		if(arr[i].x == gx && arr[i].y == gy) {
			cout << dp[i] << '\n';
			vector<pair<int, int>> ans;
			int curr = i;
			while(curr != -1) {
				ans.push_back({arr[curr].x, arr[curr].y});
				curr = par[curr];
			}
			reverse(ans.begin(), ans.end());
			cout << ans.size() << '\n';
			for(auto pr: ans) {
				cout << pr.first << ' ' << pr.second << '\n';
			}
			break;
		}
	}
}
