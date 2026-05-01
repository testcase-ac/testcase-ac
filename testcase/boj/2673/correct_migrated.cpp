#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

constexpr int V = 100;

array<array<int, V>, V> dp;
array<array<int, V>, V> e;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        e[a][b] = e[b][a] = 1;
    }

    for (int r = 1; r < V; r++) {
        for (int l = r-1; l >= 0; l--) {
            dp[l][r] = e[l][r];
            for (int k = l+1; k < r; k++) {
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + e[l][r]);
            }
        }
    }

    cout << dp[0][99] << "\n";

    return 0;
}
