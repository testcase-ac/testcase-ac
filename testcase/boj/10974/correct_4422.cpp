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
	int n;
	cin >> n;
	vector<int> arr(n);
	rep(i, n) arr[i] = i+1;
	do {
		rep(i, n) cout << arr[i] << ' ';
		cout << '\n';
	} while(next_permutation(arr.begin(), arr.end()));
}
