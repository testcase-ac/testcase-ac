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
int frac(int a, int b) {
    return (a*modinv(b))%MOD;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	int ans = 0;
	for(int t: a) {
		int x = lower_bound(a.begin(), a.end(), t) - a.begin();
		int y = n - x;
		ans += frac(x, y+1);
	}
	cout << ans % MOD;
}
