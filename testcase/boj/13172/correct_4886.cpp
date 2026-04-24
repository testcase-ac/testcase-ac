#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1e9 + 7;

int modinv(int a, int b = MOD - 2) {
    int ret = 1, mult = a % MOD;
    while(b) {
        if(b & 1) ret = (ret * mult) % MOD;
        mult = (mult * mult) % MOD;
        b /= 2;
    }
    return ret;
}
int frac(int a, int b) {
    return (a * modinv(b)) % MOD;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    int ans = 0;
    while(N--) {
        int v, u;
        cin >> v >> u;
        ans = (ans + frac(u, v)) % MOD;
    }
    cout << ans;
}
