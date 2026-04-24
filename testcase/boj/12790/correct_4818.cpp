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
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		vector<int> arr(8);
		rep(i, 8) cin >> arr[i];
		rep(i, 4) arr[i] += arr[i+4];
		arr[0] = max(arr[0], 1);
		arr[1] = max(arr[1], 1);
		arr[2] = max(arr[2], 0);
		cout << (arr[0]+5*arr[1]+2*arr[2]+2*arr[3]) << '\n';
	}
}
