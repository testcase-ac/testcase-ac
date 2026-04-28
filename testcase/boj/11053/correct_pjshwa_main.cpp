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
	int max = -2147483648;
	for(int i = 0; i < n; i++){
		int min = 0;
		for(int j = 0; j < i; j++){
			if(a[j] < a[i]){
				if(min < dp[j]) min = dp[j];
			}
		}
		dp[i] = min + 1;
		if(max < dp[i]) max = dp[i];
	}
	printf("%d", max);
}