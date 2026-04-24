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

int dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};
int n;
inline bool isvalid(int r, int c) {
	return r>=0 && c>=0 && r<n && c<n;
}
int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	int arr[n][n], tofill[n][n], visited[n][n];
	rep(i, n) rep(j, n) cin >> arr[i][j];
	set0(tofill);
	set0(visited);
	queue<pair<int,int>> frontier;
	int uid = 1;
	rep(r, n) {
		rep(c, n) {
			if(arr[r][c] && !visited[r][c]) {
				queue<pair<int,int>> que;
				visited[r][c] = true;
				que.emplace(r,c);
				while(!que.empty()) {
					auto pr = que.front();
					que.pop();
					bool addtof = false;
					arr[pr.first][pr.second] = uid;
					rep(i, 4) {
						int tr = pr.first+dr[i], tc = pr.second+dc[i];
						if(!isvalid(tr,tc)) continue;
						if(arr[tr][tc] && !visited[tr][tc]) {
							que.emplace(tr, tc);
							visited[tr][tc] = true;
						}
						else if(!arr[tr][tc] && !addtof) {
							//printf("%d,%d pushed to frontier with uid=%d\n", pr.first, pr.second, uid);
							frontier.emplace(pr.first, pr.second);
							addtof = true;
						}
					}					
				}
				uid++;
			}
		}
	}
	int t = 0;
	while(1) {
		/*
		rep(i, n) {
			rep(j, n) {
				cout << arr[i][j] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
		*/
		int ans = 0;
		int s = sz(frontier);
		while(s--) {
			auto pr = frontier.front();
			frontier.pop();
			rep(i, 4) {
				int tr = pr.first+dr[i], tc = pr.second+dc[i];
				if(!isvalid(tr,tc)) continue;
				if(arr[tr][tc] && arr[tr][tc] != arr[pr.first][pr.second]) {
					return !(cout << t);
				}
				if(tofill[tr][tc] && tofill[tr][tc] != arr[pr.first][pr.second]) {
					ans = t+1;
				}
				if(arr[tr][tc] == 0 && !tofill[tr][tc]) {
					tofill[tr][tc] = arr[pr.first][pr.second];
					frontier.emplace(tr, tc);
				}
			}
		}
		if(ans)
			return !(cout << ans);
		rep(i, n) {
			rep(j, n) {
				if(tofill[i][j])
					arr[i][j] = tofill[i][j];
			}
		}
		set0(tofill);
		t += 2;
	}
}
