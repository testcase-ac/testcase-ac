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
	rep(i, n) cin >> arr[i];
	int b, c;
	cin >> b >> c;
	ll ans = n;
	rep(i, n) arr[i] -= b;
	rep(i, n) {
		if(arr[i] > 0)
			ans += ((arr[i] % c == 0) ? (arr[i] / c) : (arr[i] / c + 1));
	}
	cout << ans;

}
