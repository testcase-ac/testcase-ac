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
    cin.tie(0)->sync_with_stdio(0);
    int R, C, K;
    cin >> R >> C >> K;
    map<int, vector<int>> mp;
    int tile = 0, ways = 1;
    while(K--) {
        int r, c;
        cin >> r >> c;
        mp[r].push_back(c);
    }
    int norow = R - mp.size();
    tile += norow * (C / 2);
    if(C % 2) {
        ways *= modinv(C / 2 + 1, norow);
        ways %= MOD;
    }
    for(auto &[r, v]: mp) {
        sort(v.begin(), v.end());
        int cur = 1;
        for(int c: v) {
            int dist = c - cur;
            cur = c + 1;
            if(dist >= 2) {
                tile += dist / 2;
                if(dist % 2) {
                    ways *= (dist / 2 + 1);
                    ways %= MOD;
                }
            }
        }
        int dist = C + 1 - cur;
        if(dist >= 2) {
            tile += dist / 2;
            if(dist % 2) {
                ways *= (dist / 2 + 1);
                ways %= MOD;
            }
        }
    }
    cout << tile << ' ' << ways;
}
