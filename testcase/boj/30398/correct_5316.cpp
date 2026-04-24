#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MX = 1e6 + 2, MOD = 1e9+7;
int fact[MX];
int modinv(int a, int b=MOD-2) {
    int ret = 1, mult = a;
    while(b) {
        if(b&1) ret = (ret * mult) % MOD;
        mult = (mult * mult) % MOD;
        b /= 2;
    }
    return ret;
}
int nCr(int n, int r) {
    if(r == 0 || n == r) return 1;

    int res = (((fact[n] * modinv(fact[r])) % MOD) * modinv(fact[n-r])) % MOD;
    return res;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, d, P;
    cin >> N >> d >> P;
    fact[1] = 1;
    for(int i=2; i<MX; i++) {
        fact[i] = (fact[i-1] * i)%MOD;
    }
    vector<vector<int>> arr(P);
    for(auto &v: arr) {
        v.resize(d);
        for(int &t: v) {
            cin >> t;
        }
    }
    vector<int> st(d), ed(d);
    for(int i=0; i<d; i++) {
        st[i] = 1;
        ed[i] = N;
    }
    arr.insert(arr.begin(), st);
    arr.push_back(ed);
    int ans = 1;
    for(int i=0; i<arr.size()-1; i++) {
        auto &cur = arr[i], &nxt = arr[i+1];
        // printf("at i = %d\n", i);
        int total = 0;
        for(int j=0; j<d; j++) {
            int dist = nxt[j] - cur[j];
            if(dist < 0) {
                return !(cout << 0);
            }
            total += dist;
        }
        // printf("  total = %d\n", total);
        for(int j=0; j<d; j++) {
            int dist = nxt[j] - cur[j];
            // printf("  compute nCr(%d, %d)\n", total, dist);
            ans *= nCr(total, dist);
            ans %= MOD;
            total -= dist;
        }
    }
    cout << ans;
}
