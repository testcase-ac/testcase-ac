#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <functional>
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
#define def function
#define deb(v) cout << #v << ':' << v << '\n';
#define ldb long double
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	pair<int,int> a[n];
	rep(i,n) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a, a+n);
	int ans = 0;
	rep(i, n) {
		if(i < a[i].second)
			ans = max(ans, a[i].second - i);
	}
	cout << ans+1;
}
