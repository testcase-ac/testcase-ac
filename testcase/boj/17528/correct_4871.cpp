#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i=0; i<n; i++)
const int MAXN = 252, MID = MAXN*MAXN;
int dp[MAXN][MID * 2];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N+1), B(N+1);
    for(int i=1; i<=N; i++) cin >> A[i] >> B[i];
    memset(dp, 0x3f, sizeof dp);
    dp[0][MID] = 0;
    for(int i=1; i<=N; i++) {
        for(int diff=0; diff<MID*2; diff++) {
            if(diff-A[i] >= 0) {
                int t = dp[i-1][diff-A[i]];
                if(diff > MID) {
                    t += min(diff-MID, A[i]);
                }
                dp[i][diff] = min(dp[i][diff], t);

            }

            if(diff+B[i] < MID*2) {
                int t = dp[i-1][diff+B[i]];
                if(diff < MID) {
                    t += min(MID-diff, B[i]);
                }
                dp[i][diff] = min(dp[i][diff], t);
            }

        }
    }
    cout << *min_element(dp[N], dp[N]+MID*2);
}
