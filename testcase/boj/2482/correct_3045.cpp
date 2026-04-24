#include <bits/stdc++.h>
using namespace std;

/*
array: [0,n-1]
Choose first -> choose k-1 in [1,n-2]
Don't choose first -> choose k in [1,n-1]
*/
#define mod 1000000003
int dp[1000][1000];
// dp[i][j]: From *linear* list of length i where anything can be chosed, choose j.
int main() {
	int n, k;
	cin >> n >> k;
	if(n < 2*k) return !(cout << 0);
	for(int i=0; i<n; i++) {
		dp[i][0] = 1;
        dp[i][1] = i;
	}
	for(int i=0; i<n; i++) {
		for(int j=2; i>=2*j-1; j++) {
			dp[i][j] = (dp[i-2][j-1] + dp[i-1][j]) % mod;
		}
	}
	cout << (dp[n-1][k] + dp[n-3][k-1]) % mod;
}
