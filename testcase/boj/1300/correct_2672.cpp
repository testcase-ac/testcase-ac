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
	int n, k;
	cin >> n >> k;
	int l = 1, r = 1000000000, mid;
	while(1) {
		mid = (l+r) / 2;
		int lb = 1, ub = 1;
		for(int i=1; i<=n; i++) {
			lb += min(n, (mid-1)/i);
			ub += min(n, mid/i);
		}
		if(k < lb)
			r = mid - 1;
		else if(k >= ub)
			l = mid + 1;
		else
			return !(cout << mid);
	}
}
