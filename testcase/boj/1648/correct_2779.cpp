#include <bits/stdc++.h>
using namespace std;
int dp[300][1<<14], MOD = 9901, n, m;
int f(int i, int bm) {
	if(i == n*m)
		return bm ? 0 : 1;
	if(dp[i][bm] != -1)
		return dp[i][bm];
	int& r = dp[i][bm];
	if(bm&1)
		return r = f(i+1, bm>>1);
	r = f(i+1, (bm>>1)|(1<<(m-1)));
	if(!(bm&3) && i%m != m-1)
		r += f(i+1, (bm>>1)|1);
	r %= MOD;
	return r;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	memset(dp, -1, sizeof dp);
	cout << f(0, 0);
}
