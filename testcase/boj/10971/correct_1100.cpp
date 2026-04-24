#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

#define MOD 1000000007
using namespace std;
#define MAXN 10
int n;
int arr[MAXN][MAXN];
int minans = INT_MAX;
vector<bool> visited;
void dfs(int start, int visiting, int ans) {
	bool allvisit = true;
	rep(i, n) {
		if(!visited[i]) {
			allvisit = false;
			break;
		}
	}
	if(allvisit) {
		if(arr[visiting][start]) {
			minans = min(minans, ans+arr[visiting][start]);
		}
	}
	rep(i, n) {
		if(arr[visiting][i] && !visited[i]) {
			allvisit = false;  // allvisit should be set to false if !visited[i]. However, it is set when arr[visiting][i] && !visited[i]
			visited[i] = true;
			dfs(start, i, ans+arr[visiting][i]);
			visited[i] = false;
		}
	}
}

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	rep(i, n) rep(j, n) cin >> arr[i][j];
	visited.resize(n);
	rep(i, n) {
		visited[i] = true;
		dfs(i, i, 0);
		visited[i] = false;
	}
	cout << minans;


}
