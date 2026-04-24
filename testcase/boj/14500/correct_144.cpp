#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MAXN 500
int arr[MAXN][MAXN];
int n, m;
int ans;
void matchpattern(vector<pair<int,int>> pattern) {
	int dr = 0, dc = 0;
	for(auto p: pattern) {
		dr = max(dr, p.first);
		dc = max(dc, p.second);
	}
	rep(r, n-dr) {
		rep(c, m-dc) {
			int sum = 0;
			for(auto p: pattern)
				sum += arr[r+p.first][c+p.second];
			ans = max(ans, sum);
		}
	}

}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n >> m;
	rep(i, n) rep(j, m) cin >> arr[i][j];
	matchpattern({{0,0},{0,1},{0,2},{0,3}});
	matchpattern({{0,0},{1,0},{2,0},{3,0}});

	matchpattern({{0,0},{0,1},{1,0},{1,1}});

	matchpattern({{0,0},{1,0},{2,0},{2,1}});
	matchpattern({{0,0},{1,0},{0,1},{0,2}});
	matchpattern({{0,0},{0,1},{1,1},{2,1}});
	matchpattern({{1,0},{1,1},{1,2},{0,2}});
	matchpattern({{2,0},{2,1},{1,1},{0,1}});
	matchpattern({{0,0},{1,0},{1,1},{1,2}});
	matchpattern({{0,0},{0,1},{1,0},{2,0}});
	matchpattern({{0,0},{0,1},{0,2},{1,2}});

	matchpattern({{0,0},{1,0},{1,1},{2,1}});
	matchpattern({{1,0},{1,1},{0,1},{0,2}});
	matchpattern({{0,1},{1,1},{1,0},{2,0}});
	matchpattern({{0,0},{0,1},{1,1},{1,2}});

	matchpattern({{0,0},{0,1},{0,2},{1,1}});
	matchpattern({{1,0},{0,1},{1,1},{2,1}});
	matchpattern({{1,0},{1,1},{1,2},{0,1}});
	matchpattern({{0,0},{1,0},{2,0},{1,1}});
	cout << ans;
}
