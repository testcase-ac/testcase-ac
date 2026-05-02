#include <iostream>
#include <array>

using namespace std;

array<array<int, 262146>, 61> dp;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int res = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        dp[x][i] = i+1;
        res = max(res, x);
    }
    
    for (int k = 1; k <= res; k++) {
        for (int i = 1; i <= n; i++) {
            if (!dp[k][dp[k][i]]) { continue; }
            dp[k+1][i] = dp[k][dp[k][i]];
            res = max(res, k+1);
        }
    }

    cout << res << "\n";

    return 0;
}
