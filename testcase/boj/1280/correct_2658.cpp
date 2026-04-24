#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <functional>
#include <string>
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
inline int lsb(int i) {return i & -i;}
struct BIT {
	vector<ll> bit;
	int n;
	BIT(int _n) {
		n = _n;
		bit.resize(n+1);
	};
	void update(int i, ll v) {
		while(i <= n) {
			bit[i] += v;
			i += lsb(i);
		}
	}
	ll query(int i) {
		ll ret = 0;
		while(i) {
			ret += bit[i];
			i -= lsb(i);
		}
		return ret;
	};
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> arr(n+1), p2sp(n+1); // position -> sorted position mapping
	vector<pair<int,int>> temp(n);
	rep(i,n) {
		cin >> arr[i+1];
		temp[i].first = arr[i+1];
		temp[i].second = i+1;
	}
	sort(temp.begin(), temp.end());
	rep(i, n) p2sp[temp[i].second] = i+1;
	BIT cntbit(n), numbit(n);
	ll ans = 1;
	for(int i=1; i<=n; i++) {
		if(i > 1) {
			int lgcnt = (int)cntbit.query(p2sp[i]), smcnt = i - lgcnt - 1;
			ll tomult = ((ll)arr[i] * (lgcnt - smcnt) + numbit.query(n) - 2*numbit.query(p2sp[i])) % MOD;
			//printf("tomult at %d: %lld. lgcnt=%d, smcnt=%d\n", i, tomult, lgcnt, smcnt);
			ans = (ans * tomult) % MOD;
		}
		cntbit.update(p2sp[i], 1);
		numbit.update(p2sp[i], arr[i]);
	}
	cout << ans;
}
