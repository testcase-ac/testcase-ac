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
/*
arr		1 2 1 3 2 5
lis_len	1 2
got		1 2 0 2 2 2

1 5 2 3 4
*/
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> arr(n);
	vector<int> lis_len(n);  // lis_len[i]: length of lis that has i as its last elem
	rep(i, n) cin >> arr[i];
	rep(i, n) lis_len[i] = 1;
	for(int i=1; i<n; i++) {
		for(int j=0; j<i; j++) {
			if(arr[j] < arr[i] && lis_len[j] >= lis_len[i])
				lis_len[i] = lis_len[j] + 1;
		}
	}
	int ans = 0;
	rep(i, n) {
		ans = (ans > lis_len[i] ? ans : lis_len[i]);
	}
	cout << ans;

}
