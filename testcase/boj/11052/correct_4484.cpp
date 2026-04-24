#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

#define MAXN 1000
int dp[MAXN+1];

int main() {
	int n;
	cin >> n;
	vector<int> arr(n+1);
	rep(i, n) cin >> arr[i+1];
	for(int i=1; i<=n; i++) {
		int tempmax = arr[i];
		for(int j=1;j<i;j++) {
			if(dp[j]+dp[i-j] > tempmax)
				tempmax = dp[j] + dp[i-j];
		}
		dp[i] = tempmax;
	}
	cout << dp[n];
}
