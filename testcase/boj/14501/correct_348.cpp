#include <stdio.h>

int arr[16][2];
int dp[16];
int max(int n, int m) {
	return n>m?n:m;
}
int main() {
	
	int n, ans=0;
	
	scanf("%d", &n);
	
	for (int i=1; i<=n; i++){
		scanf("%d %d", &arr[i][0], &arr[i][1]);
	}
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=i; j++) {
			if (j+arr[j][0]-1==i) {
				dp[i]=max(dp[i], dp[i-arr[j][0]]+arr[j][1]);
			}
		}
        dp[i] = max(ans, dp[i]);
		ans = max(ans, dp[i]);
	}
	for (int i=1; i<=n; i++) {
		ans = max(ans, dp[i]);
	}
	printf("%d", ans);
}
