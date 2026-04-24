#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define deb(v) cout << #v << ':' << v

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> dp(n, MOD);
	int ans = 0;
	rep(i, n) {
		int x;
		cin >> x;
		auto it = lower_bound(dp.begin(), dp.end(), x);
		ans = max(ans, (int)(it-dp.begin())+1);
		*it = x;
	}
	cout << ans;
}
