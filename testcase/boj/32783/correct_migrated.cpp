#include <bits/stdc++.h>
using namespace std;
using L = long long;
const L MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    L n, c1, c2;
    cin >> n;

    vector<L> w(n);
    for (int i = 0; i < n; i++) {
        L a, m;
        cin >> a >> m;
        w[i] = a * m / 625;
    }

    cin >> c1 >> c2;

    vector<L> dp(c2 + 1, 0);
    dp[0] = 1;

    for (L cost : w) {
        if (cost > c2) continue;
        for (int s = c2; s >= cost; s--) {
            dp[s] += dp[s - cost];
            if (dp[s] >= MOD) dp[s] -= MOD;
        }
    }

    L ans = 0;
    for (int s = c1; s <= c2; s++) ans = (ans + dp[s]) % MOD;

    cout << ans;
    return 0;
}
