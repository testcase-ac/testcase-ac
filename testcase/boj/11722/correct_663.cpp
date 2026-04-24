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
	vector<int> arr(n);
	vector<int> lds_len(n);  // lds_len[i]: length of lds that has i as its last elem
	rep(i, n) cin >> arr[i];
	rep(i, n) lds_len[i] = 1;
	for(int i=1; i<n; i++) {
		for(int j=0; j<i; j++) {
			if(arr[j] > arr[i] && lds_len[j] >= lds_len[i])
				lds_len[i] = lds_len[j] + 1;
		}
	}
	int ans = 0;
	rep(i, n) {
		ans = (ans > lds_len[i] ? ans : lds_len[i]);
	}
	cout << ans;

}
