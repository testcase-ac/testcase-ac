#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <vector>
#include <stack>
#include <algorithm>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

#define MAXN 100
int arr[MAXN][MAXN];

int main() {
	int m, n, k, x1, y1, x2, y2;
	cin >> m >> n >> k;
	rep(i, k) {
		cin >> x1 >> y1 >> x2 >> y2;
		for(int i=y1; i<y2; i++) {  // had bug: reversed x and y
			for(int j=x1; j<x2; j++) {
				arr[i][j] = 1;
			}
		}
	}

	vector<int> ans;
	rep(i, m) {
		rep(j, n) {
			if(arr[i][j] == 0) {
				stack<pair<int,int>> stk;
				stk.emplace(i, j);
				arr[i][j] = 1;  // had bug: prevent self-revisit
				int cnt = 0;
				while(!stk.empty()) {
					int ti, tj;
					auto pt = stk.top();
					stk.pop();
					cnt++;
					ti = pt.first;
					tj = pt.second;
					if(ti+1<m && arr[ti+1][tj] == 0) {
						arr[ti+1][tj] = 1;
						stk.emplace(ti+1, tj);
					}
					if(ti-1>=0 && arr[ti-1][tj] == 0) {
						arr[ti-1][tj] = 1;
						stk.emplace(ti-1, tj);
					}
					if(tj+1<n && arr[ti][tj+1] == 0) {
						arr[ti][tj+1] = 1;
						stk.emplace(ti, tj+1);
					}
					if(tj-1>=0 && arr[ti][tj-1] == 0) {
						arr[ti][tj-1] = 1;
						stk.emplace(ti, tj-1);
					}
				}
				ans.push_back(cnt);
			}
		}
	}
	sort(ans.begin(), ans.end());
	cout << sz(ans) << '\n';
	for(int i:ans)
		cout << i << ' ';
}
