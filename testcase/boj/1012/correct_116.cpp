#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>
#include <stack>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int m, n, k, x, y;
		cin >> m >> n >> k;
		int arr[m][n]; set0(arr);
		rep(i, k) {
			cin >> x >> y;
			arr[x][y] = 1;
		}
		int ans = 0;
		rep(i, m) {
			rep(j, n) {
				if(arr[i][j] != 1) continue;
				stack<pair<int,int>> stk;
				stk.emplace(i, j);
				while(!stk.empty()) {
					auto p = stk.top();
					stk.pop();
					int a = p.first, b = p.second;
					if(a+1<m && arr[a+1][b] == 1) {
						stk.emplace(a+1, b);
						arr[a+1][b] = 2;
					}
					if(a-1>=0 && arr[a-1][b] == 1) {
						stk.emplace(a-1,b);
						arr[a-1][b] = 2;
					}
					if(b+1<n && arr[a][b+1] == 1) {
						stk.emplace(a, b+1);
						arr[a][b+1] = 2;
					}
					if(b-1>=0 && arr[a][b-1] == 1) {
						stk.emplace(a, b-1);
						arr[a][b-1] = 2;
					}
				}
				ans++;
			}
		}
		cout << ans << '\n';

	}
}
