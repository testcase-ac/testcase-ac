#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> arr(n), dp(n, 1);
	rep(i, n) cin >> arr[i];
	for(int i=1; i<n; i++) {
		for(int j=0; j<i; j++) {
			if(arr[i] > arr[j])
				dp[i] = max(dp[i], dp[j]+1);
		}
	}
	int maxdp=0;
	rep(i, n) maxdp = max(maxdp, dp[i]);
	cout << (n-maxdp);

}
