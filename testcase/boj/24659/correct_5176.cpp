#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5 + 1;
int N, P[MX], A[MX], B[MX];
bool seen[MX];
int solve(vector<int> a, vector<int> b) {
    int n = a.size();
    vector<vector<int>> dp(2, vector<int>(2*n+1));
    dp[0][0] = INT_MAX;
    int ans = LLONG_MAX;
    for(int i=1; i<=2*n; i++) {
        int t = (i - 1) % n;
        dp[0][i] = min(dp[0][i-1] + a[t], dp[1][i-1] + a[t] + b[t]);
        dp[1][i] = min(dp[0][i-1] + b[t], dp[1][i-1] + b[t]);
        if(i >= n) {
            int th = min(dp[0][i-n], dp[1][i-n]);
            ans = min({ans, dp[0][i] - th, dp[1][i] - th});
        }
    }
    return ans;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> P[i];
    }
    for(int i=1; i<=N; i++) {
        cin >> A[i];
    }
    for(int i=1; i<=N; i++) {
        cin >> B[i];
    }
    int ans = 0;
    for(int i=1; i<=N; i++) {
        if(seen[i] || i == P[i]) continue;
        int cur = i;
        vector<int> v, a, b; 
        do {
            seen[cur] = true;
            v.push_back(cur);
            cur = P[cur];
        } while(cur != i);
        a.resize(v.size());
        b.resize(v.size());
        for(int t=0; t<v.size(); t++) {
            a[t] = A[v[t]];
            b[t] = B[v[t]];
        }

        int trivial = accumulate(a.begin(), a.end(), 0ll);

        int tmp = solve(a, b);
        ans += min({tmp, trivial});
    }
    cout << ans;
}
