#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cassert>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int n, m;
inline bool isvalid(int r, int c) {
	return r >= 0 && c >= 0 && r < n && c < m;
}
int dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n >> m;
	int arr[n][m];
    int sum = 0;
	rep(i,n) rep(j,m) {
        cin >> arr[i][j];
        sum += arr[i][j];
    }
    assert(sum > 0);
	queue<pair<int,int>> que, cque;
	int visitcnt[n][m];
	set0(visitcnt);
	que.emplace(0,0);
	while(!que.empty()) {
		auto pr = que.front();
		que.pop();
		int r = pr.first, c = pr.second;
		rep(i,4) {
			int tr = r+dr[i], tc = c+dc[i];
			if(!isvalid(tr,tc)) continue;
			if(arr[tr][tc] == 0 && !visitcnt[tr][tc]) {
				que.emplace(tr, tc);
				visitcnt[tr][tc] = 1;
			} else if(arr[tr][tc] == 1){
				visitcnt[tr][tc]++;
				if(visitcnt[tr][tc] == 2) {
					cque.emplace(tr, tc);
				}
			}
		}
	}
	//printf("cque is set. sz(cque)=%d\n", sz(cque));
	int t = 0;
	while(!cque.empty()) {
		int s = sz(cque);
		while(s--) {
			auto pr = cque.front();
			cque.pop();
			int r = pr.first, c = pr.second;
			rep(i,4) {
				int tr = r+dr[i], tc = c+dc[i];
				if(!isvalid(tr,tc)) continue;
				if(arr[tr][tc] == 0 && !visitcnt[tr][tc]) {
					que.emplace(tr, tc);
					visitcnt[tr][tc] = 1;
				} else if(arr[tr][tc] == 1) {
					visitcnt[tr][tc]++;
					if(visitcnt[tr][tc] == 2)
						cque.emplace(tr, tc);
				}
			}
		}
		while(!que.empty()) {
			auto pr = que.front();
			que.pop();
			int r = pr.first, c = pr.second;
			rep(i,4) {
				int tr = r+dr[i], tc = c+dc[i];
				if(!isvalid(tr,tc)) continue;
				if(arr[tr][tc] == 0 && !visitcnt[tr][tc]) {
					que.emplace(tr, tc);
					visitcnt[tr][tc] = 1;
				} else if(arr[tr][tc] == 1) {
					visitcnt[tr][tc]++;
					if(visitcnt[tr][tc] == 2)
						cque.emplace(tr, tc);
				}
			}
		}
		t++;
		//printf("cque at t=%d end is %d\n", t, sz(cque));
	}
	cout << t;
}
