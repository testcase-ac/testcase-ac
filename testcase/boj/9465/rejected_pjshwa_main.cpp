#include <cstdio>

int dp[100000][2];
int a[100000][2];
int n;

int opt(int n, int col, int selection){
	if(n - 1 == col){
		return a[n-1][selection];
	}
	else {
		if(dp[col+1][0] == -1) dp[col+1][0] = opt(n, col + 1, 0);
		if(dp[col+1][1] == -1) dp[col+1][1] = opt(n, col + 1, 1);
		dp[col][selection] = a[col][selection] + dp[col+1][(selection+1)%2] > dp[col+1][selection] ? a[col][selection] + dp[col+1][(selection+1)%2] : dp[col+1][selection];
		return dp[col][selection];
	}
}

int main(){
	int t;
	scanf("%d", &t);
	for(int idx = 0; idx < t; idx++){
		scanf("%d", &n);
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < n; j++){
				dp[j][i] = -1;
				scanf("%d", &a[j][i]);
			}
		}
		opt(n, 0, 0); opt(n, 0, 1);
		printf("%d\n", dp[0][0] > dp[0][1] ? dp[0][0] : dp[0][1] );
	}
}