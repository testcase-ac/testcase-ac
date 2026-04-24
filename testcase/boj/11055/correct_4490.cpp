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

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> arr(n), lis_sum(n);  // lis_sum[i]: sum of subsequence that has i as its last elem
	rep(i, n) {
		cin >> arr[i];
		lis_sum[i] = arr[i];
		rep(j, i) {
			if(arr[j] < arr[i])
				lis_sum[i] = max(lis_sum[i], lis_sum[j] + arr[i]);
		}
	}
	int ans = lis_sum[0];
	rep(i, n) ans = max(ans, lis_sum[i]);
	cout << ans;



}
