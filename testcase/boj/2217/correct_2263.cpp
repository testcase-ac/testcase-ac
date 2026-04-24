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

bool rev(int a, int b) {
	return a>b;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> arr(n);
	rep(i, n) cin >> arr[i];
	sort(arr.begin(), arr.end(), rev);
	int ans = 0;
	rep(k, n) {
		ans = max(ans, arr[k] * (k+1));
	}
	cout << ans;
}
