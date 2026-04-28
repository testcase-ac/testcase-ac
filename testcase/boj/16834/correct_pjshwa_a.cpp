#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
#include<string>
#include<cstring>
#include<stack>
#include<map>
#include<set>
#include<deque>
#include<functional>
#include<unordered_map>
#include<list>
#include<cstdlib>
#include<ctime>
#include<cassert>

#define double long double
//T.erase(unique(T.begin(),T.end()),T.end());
//written by djs100201
#define all(v) v.begin(),v.end()
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ = 422 + 100, inf = 1e18 + 1, mod = 998244353, sqrtN = 333, p = 27;
ll dy[4] = { -1,0,1,0 }, dx[4] = { 0,1,0,-1 };
ll n, m, k, tc = 1, a, b, c, sum, x, y, z, w, base, ans;
ll gcd(ll x, ll y) {
	if (!y)return x;
	return gcd(y, x % y);
}
ll get(ll x) {
	ll ret = 0, sum = 0;
	ll l = 1, r = 0;
	while (1) {
		if (sum == x)ret++;
		if (sum <= x) {
			r++;
			sum += r;
		}
		else {
			sum -= l;
			l++;
		}
		if (r > x)break;
	}
	return ret;
}
void solve() {
	cin >> n;
	for (ll i = 1; i * i <= n; i++) {
		if (n % i)continue;
		x = i, y = n / i;
		a = get(x), b = get(y);
		ans += a * b;
		if (x == y)continue;
		ans += a * b;
	}
	cout << ans;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//cin >> tc;
	while (tc--)solve();
}

// https://www.acmicpc.net/source/33187817
// by djs100201
