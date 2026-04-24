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
	int n, m, k;
	cin >> n >> m >> k;
	int maxgroup = min(n/2, m);
	int remainingppl = (n+m) - maxgroup*3;
	k -= remainingppl;
	cout << maxgroup - (k <= 0 ? 0: (k+2)/3);
}
