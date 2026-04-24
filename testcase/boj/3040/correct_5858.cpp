#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <numeric>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	vector<int> arr(9);
	rep(i, 9) cin >> arr[i];
	sort(arr.begin(), arr.end());
	do {
		if(accumulate(arr.begin(), arr.begin()+7, 0) == 100) {
			rep(i, 7) cout << arr[i] << '\n';
			return 0;
		}
	} while(next_permutation(arr.begin(), arr.end()));
}
