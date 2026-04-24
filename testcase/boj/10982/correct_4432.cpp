#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
int solve() {
    int N;
    cin >> N;
    vector<pair<int, int>> v(N);
    for(auto &[a, b]: v) {
        cin >> a >> b;
    }
    vector<int> dp(MX+102, 0x3f3f3f3f), nxt(MX+102, 0x3f3f3f3f);
    dp[0] = 0;
    for(auto [a, b]: v) {
        fill(nxt.begin(), nxt.end(), 0x3f3f3f3f);
        for(int i=0; i<MX; i++) {
            nxt[i+a] = min(nxt[i+a], dp[i]);
            nxt[i] = min(nxt[i], dp[i]+b);
        }
        swap(nxt, dp);
    }
    int ans = 0x3f3f3f3f;
    for(int i=0; i<MX; i++) {
        ans = min(ans, max(i, dp[i]));
    }
    return ans;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--)
        cout << solve() << '\n';
}
