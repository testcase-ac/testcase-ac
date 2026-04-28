#include <cstdio>

long long dp[201][201];
const int m = 1000000000;
long long sum_decompose(int n, int k);
int main(){
	
	for(int i = 0; i < 201; i++){
		for(int j = 0; j < 201; j++){
			dp[i][j] = 0;
		}
	}
	
	for(int i = 0; i < 201; i++){
		dp[1][i] = i;
		dp[i][1] = 1;
	}

	int n, k;
	scanf("%d%d", &n, &k);

	printf("%lld", sum_decompose(n, k));
}

long long sum_decompose(int n, int k){
	long long ans = 0;
	if(k == 1) return 1;
	for(int i = 0; i <= n; i++){
		if(dp[i][k-1]) ans += dp[i][k-1];
		else ans += sum_decompose(i, k-1);
	}
	dp[n][k] = ans % m;
	return dp[n][k];
}