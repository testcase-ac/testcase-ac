#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
int modinv(int a, int b=MOD-2) {
    int ret = 1, mult = a % MOD;
    while(b) {
        if(b&1) ret = (ret*mult)%MOD;
        mult = (mult*mult)%MOD;
        b /= 2;
    }
    return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	if(n == 1)
		return !(cout << m);
	deque<int> dq = {m};
	int csum = m;
	for(int i=2; i<=n; i++) {
		dq.push_front((csum*(m-1))%MOD);
		csum += dq.front();
		if(dq.size() > k-1) {
			csum -= dq.back();
			dq.pop_back();
		}
		csum = (csum + MOD) % MOD;
	}
	cout << (modinv(m, n) - csum + MOD) % MOD;
}
