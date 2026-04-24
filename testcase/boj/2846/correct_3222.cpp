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
	vector<int> arr(n);
	int begin, ans = 0;
	bool increasing = false;
	rep(i, n) cin >> arr[i];
	for(int i=1; i<n; i++) {
		if(arr[i] > arr[i-1]) {
			if(!increasing)
				begin = arr[i-1];
			increasing = true;
		} else {
			if(increasing)
				ans = max(ans, arr[i-1]-begin);
			increasing = false;
		}
	}
	if(increasing)
		ans = max(ans, arr[n-1]-begin);
	cout << ans;
}
