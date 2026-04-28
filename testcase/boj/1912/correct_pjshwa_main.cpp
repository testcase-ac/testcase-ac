#include <cstdio>

int main(){
	int n;
	

	scanf("%d", &n);

	int a[n];
	int dp[n];
	
	for(auto &x : dp){
		x = 0;
	}
	
	for(auto &x : a){
		scanf("%d", &x);
	}

	dp[0] = a[0];

	for(int i = 1; i < n; i++){
		if(dp[i - 1] + a[i] > a[i]){
			dp[i] = dp[i - 1] + a[i];
		}
		else dp[i] = a[i];
	}

	int max = -2147483648;
	for(auto &x : dp){
		if(max < x) max = x;
	}

	printf("%d", max);
}