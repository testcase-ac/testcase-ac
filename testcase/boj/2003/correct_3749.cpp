#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	int arr[n+1], accsum[n+1];
	rep(i, n) cin >> arr[i+1];
	rep(i, n) accsum[i+1] = accsum[i] + arr[i+1];
	int ans = 0;
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<=n; j++) {
			if(accsum[j] - accsum[i] == m)
				ans++;
		}
	}
	cout << ans;

}
