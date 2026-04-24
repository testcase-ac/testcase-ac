#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353, MX = 300001;
int f[MX];
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
int nCr(int n, int r) {
    return frac(f[n], f[r] * f[n-r]);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    f[0] = 1;
    for(int i=1; i<MX; i++) {
        f[i] = (f[i-1] * i) % MOD;
    }
    int N, M;
    cin >> N >> M;
    int st = N / 2;
    int r = st - M, n = N;
    if(r < 0 || r > n) {
        return !(cout << 0);
    }
    cout << nCr(n, r);

}
