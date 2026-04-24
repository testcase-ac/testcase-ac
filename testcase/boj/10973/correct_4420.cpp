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
	int n;
	cin >> n;
	vector<int> arr(n);
	rep(i, n) cin >> arr[i];
	bool r = prev_permutation(arr.begin(), arr.end());
	if(!r)
		cout << -1;
	else
		rep(i,n) cout << arr[i] << ' ';

}
