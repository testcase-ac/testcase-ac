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

#define FAIL "KAKTUS"
#define STONE 'X'
#define WATER '*'
#define EMPTY '.'
#define DOCHI 'S'
#define GOAL 'D'

using namespace std;
int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
int R, C;
inline bool isvalid(int r, int c) {
	return r>=0 && c>=0 && r<R && c<C;
}
int main() {
	cin >> R >> C;
	vector<string> arr(R);
	rep(i, R) cin >> arr[i];
	queue<pair<int,int>> waterque, dochique;
	rep(i, R) {
		rep(j, C) {
			if(arr[i][j] == WATER)
				waterque.emplace(i, j);
			else if(arr[i][j] == DOCHI) {
				dochique.emplace(i, j);
				arr[i][j] = '.';
			}
		}
	}
	int t = 0;
	while(++t) {
		int s = sz(waterque);
		while(s--) {
			auto pr = waterque.front();
			waterque.pop();
			rep(i, 4) {
				int tr = pr.first+dr[i], tc = pr.second+dc[i];
				if(isvalid(tr,tc) && (arr[tr][tc] == EMPTY || arr[tr][tc] == DOCHI)) {
					arr[tr][tc] = '*';
					waterque.emplace(tr, tc);
				}
			}
		}
		s = sz(dochique);
		while(s--) {
			auto pr = dochique.front();
			dochique.pop();
			rep(i, 4) {
				int tr = pr.first+dr[i], tc = pr.second+dc[i];
				if(!isvalid(tr,tc)) continue;
				if(arr[tr][tc] == EMPTY) {
					arr[tr][tc] = DOCHI;
					dochique.emplace(tr, tc);
				} else if(arr[tr][tc] == GOAL)
					return !(cout << t);
			}
		}
		if(dochique.empty()) {
			return !(cout << FAIL);
		}
	}
}
