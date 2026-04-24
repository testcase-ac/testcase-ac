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
int R, C;
inline int isvalid(int r, int c) {return r>=0 && c>=0 && r<R && c<C;}
int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	
	cin >> R >> C;
	vector<string> arr(R);
	rep(i, R) cin >> arr[i];
	bool visited[R][C]; set0(visited);
	int dp[R][C];
	rep(r, R) rep(c, C) dp[r][c] = MOD;
	queue<pair<int,int>> que0, que1;
	que0.emplace(0,0);
	int ans = MOD;
	int dist = 1;
	while(!que0.empty()) {
		int s = sz(que0);
		while(s--) {
			auto q = que0.front();
			que0.pop();
			int r = q.first, c = q.second;
			if(r == R-1 && c == C-1)
				ans = dist;
			rep(i, 4) {
				int tr = r+dr[i], tc = c+dc[i];
				if(!isvalid(tr,tc) || visited[tr][tc]) continue;
				if(arr[tr][tc] == '0') {
					visited[tr][tc] = true;
					que0.emplace(tr, tc);
				} else if(arr[tr][tc] == '1' && dist+1 < dp[tr][tc]) {
					dp[tr][tc] = dist+1;
					que1.emplace(tr, tc);
				}
			}			
		}
		dist++;
	}
	while(!que1.empty()) {
		auto q = que1.front();
		que1.pop();
		int r = q.first, c = q.second;
		rep(i, 4) {
			int tr = r+dr[i], tc = c+dc[i];
			if(!isvalid(tr,tc) || arr[tr][tc] != '0') continue;
			if(dp[tr][tc] > dp[r][c] + 1) {
				dp[tr][tc] = dp[r][c] + 1;
				que1.emplace(tr, tc);
			}
		}
	}
	/*
	rep(r, R) {
		rep(c, C) {
			if(dp[r][c] == MOD)
				cout << "INF ";
			else
				cout << dp[r][c] << ' ';
		}
		cout << '\n';
	}
	*/
	ans = min(ans, dp[R-1][C-1]);
	cout << (ans == MOD ? -1 : ans);
}
