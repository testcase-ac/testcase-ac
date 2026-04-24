#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7, MXL = 1e7;
int fact[MXL], factinv[MXL];
int modinv(int a, int b=MOD-2) {
    int ret = 1, mult = a % MOD;
    while(b) {
        if(b&1) ret = (ret*mult)%MOD;
        mult = (mult*mult)%MOD;
        b /= 2;
    }
    return ret;
}
int ncr(int n, int r) {
	if(n < r)
		return 0;
	return ((fact[n] * factinv[r]) % MOD * factinv[n-r]) % MOD;
}
int solve() {
	int st, ed;
	cin >> st >> ed;
	vector<int> vcnt(8);
	for(int i=1, mx=10; i<=7; i++, mx*=10) {
		if(mx >= st) {
			vcnt[i] = min(mx-1, ed) - st + 1;
		}
	}
	auto f = [&](int sz, int t) { // 크기 sz의 물음표에 t길이의 수가 들어올 화률
		return (ncr(vcnt[t], sz) - ncr(vcnt[t-1], sz) + MOD) % MOD;
	};
	auto g = [&](int sz) {
		int acc = 0;
		for(int t=1; t<=7; t++)
			acc += f(sz, t) * t;
		acc %= MOD;
		acc *= modinv(ncr(ed-st+1, sz));
		return acc % MOD;
	};
	int cnt = ed - st + 1, cur = 1, trail = 1, ans = 0;
	while(cnt > 1) {
		if(cnt % 2 == 0) {
			ans += g(cur*2) * ((cnt / 2) - 1);
			ans += g(cur+trail);
			trail += cur;
		} else {
			ans += g(cur*2) * (cnt / 2);
		}
		cur *= 2;
		cnt = (cnt + 1) / 2;
	}
	return ans % MOD;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	fact[0] = factinv[0] = fact[1] = factinv[1] = 1;
	for(int i=2; i<MXL; i++) {
		fact[i] = (fact[i-1] * i) % MOD;
	}
	factinv[MXL-1] = modinv(fact[MXL-1]);
	for(int i=MXL-2; i>=2; i--) {
		factinv[i] = (factinv[i+1] * (i+1)) % MOD;
	}
	while(n--)
		cout << solve() << '\n';
}
