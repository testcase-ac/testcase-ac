#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
inline bool isvalid(int r, int c, int n, int m) {
	return r>=0 && r<n && c>=0 && c<m;
}
int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> m >> n;
	vector<string> arr(n);
	rep(i, n)
		cin >> arr[i];
	queue<pair<int,int>> vstque, wallque;
	bool visited[n][m]; set0(visited);
	vstque.emplace(0,0);
	visited[0][0] = true;
	int ans = 0;
	while(1) {
		while(!vstque.empty()) {
			// visit. if wall, push to wallque. if (n-1,m-1): break.
			auto vst = vstque.front();
			vstque.pop();
			int r = vst.first, c = vst.second;
			if(r == n-1 && c == m-1)
				return !(cout << ans);
			rep(i, 4) {
				int tr = r+dr[i], tc = c+dc[i];
				//printf("visiting %d,%d -> %d,%d..\n", r,c,tr,tc);
				if(!isvalid(tr,tc,n,m) || visited[tr][tc]) continue;
				visited[tr][tc] = true;
				if(arr[tr][tc] == '0') {
					vstque.emplace(tr,tc);
					//printf("ans=%d: emplace %d,%d to vstque\n", ans, tr, tc);
				}
				else if(arr[tr][tc] == '1')
					wallque.emplace(tr,tc);
			}
			//printf("sz(vstque)=%d\n", sz(vstque));
		}
		vstque = wallque;
		while(!wallque.empty()) {
			// set wall to 0
			auto w = wallque.front();
			wallque.pop();
			arr[w.first][w.second] = '0';
		}
		ans++;
	}
	cout << ans;
}
