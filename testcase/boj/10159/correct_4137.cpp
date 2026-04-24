#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<bool>> reach(n, vector<bool>(n, 1));
	rep(i, n) reach[i][i] = 0;
	rep(i, m) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		reach[v][u] = 0;
	}
	rep(k, n) {
		vector<vector<bool>> nextreach = reach;
		rep(i, n) {
			rep(j, n) {
				if(reach[i][k] == 0 && reach[k][j] == 0)
					nextreach[i][j] = 0;
			}
		}
		reach = nextreach;
	}
	rep(i, n) {
		int ans = n-1;
		rep(j, n) {
			if(i == j) continue;
			if(reach[i][j] == 0) ans--;
			else if(reach[j][i] == 0) ans--;
		}
		cout << ans << '\n';
	}
}
