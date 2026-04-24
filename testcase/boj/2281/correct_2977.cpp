#include <bits/stdc++.h>
using namespace std;
const int MX = 1007;
int dp[MX][MX], n, m, arr[MX];
inline int sq(int i){return i*i;}
int f(int i, int j) {
	if(i == n-1) return 0;
	int& r = dp[i][j];
	if(r != -1) return r;
	r = f(i+1, arr[i+1])+sq(m-j);
	if(j+1+arr[i+1] <= m)
		r = min(r, f(i+1, j+1+arr[i+1]));
	return r;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	memset(dp, -1, sizeof dp);
	cout << f(0,arr[0]);
}
