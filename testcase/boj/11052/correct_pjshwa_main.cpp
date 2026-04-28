#include <cstdio>

int dp[1001];
int a[1001];

int opt(int index){
	if(index == 0) return 0;
	if(index == 1) return a[0];
	int max = a[index-1]; // itself is the best fit
	for(int i = 1; i < index / 2 + 1; i++){
		if(dp[i] == -1) dp[i] = opt(i);
		if(dp[index-i] == -1) dp[index-i] = opt(index-i);
		if(max < dp[i] + dp[index - i]) max = dp[i] + dp[index - i];
	}
	dp[index] = max;
	return dp[index];
}


int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 0; i < n + 1; i++){
		dp[i] = -1;
	}

	printf("%d\n", opt(n));

}