#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N, minOperation;
	cin >> N;
	int dp[N+1];
	dp[1] = 0;
	for(int i=2; i<=N; i++) {
		minOperation = dp[i-1];
		if(i % 2 == 0)
			minOperation = min(minOperation, dp[i/2]);
		if(i % 3 == 0)
			minOperation = min(minOperation, dp[i/3]);
		dp[i] = minOperation + 1;
	}
	cout << dp[N];
}
