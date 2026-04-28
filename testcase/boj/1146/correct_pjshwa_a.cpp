#include<bits/stdc++.h>
using namespace std;
const int MOD = 1'000'000;
int n, dp[100][100][100][2];

int solve(int here, int left, int right, bool makeRight){
	if(here == n) return 1;
	int &ret = dp[here][left][right][makeRight];
	if(ret != -1) return ret;

	ret = 0;
	if(makeRight){
		if(right == 0) return ret;
		for(int i=0; i<right; ++i)
			ret = (ret + solve(here+1, left+i, right-1-i, !makeRight))%MOD;
	}
	else{
		if(left == 0) return ret;
		for(int i=0; i<left; ++i)
			ret = (ret + solve(here+1, left-1-i, right+i, !makeRight))%MOD;
	}
	return ret;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	if(n==1){
		cout << 1;
		return 0;
	}
	memset(dp, -1, sizeof(dp));
	int ans = 0;
	for(int i=0; i<n; ++i){
		ans = (ans + solve(1, i, n-i-1, true))%MOD;
		ans = (ans + solve(1, i, n-i-1, false))%MOD;
	}
	cout << ans;
}