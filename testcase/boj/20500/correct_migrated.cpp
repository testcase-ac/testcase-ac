#include <bits/stdc++.h>
using namespace std;
const int mod=1000000007;

int main() {
	int n;
	long long dp[3][1516];
	cin>>n;

	dp[0][1]=0;
	dp[1][1]=1; 
	dp[2][1]=0;

	for (int i=2;i<=n;i++) {
		dp[0][i]=(dp[1][i-1]+dp[2][i-1])%mod;
		dp[1][i]=(dp[0][i-1]+dp[2][i-1])%mod;
		dp[2][i]=(dp[0][i-1]+dp[1][i-1])%mod;
	}
	cout<<(dp[0][n])%mod;
}
