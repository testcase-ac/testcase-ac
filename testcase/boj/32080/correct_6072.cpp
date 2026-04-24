#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()

const int MX = 1001;
pair<int,int> dp[MX][MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(2*N), nxt(2*N);
    int mxp = 0;
    rep(i, 2*N) {
        cin >> A[i];
        if(A[i] > A[mxp]) {
            nxt[mxp] = i;
            mxp = i;
        }
    }
    nxt[mxp] = 2*N;
    memset(dp, -1, sizeof dp);
    dp[0][0] = {0,0};
    for(int i=0; i<=N; i++) {
        for(int j=0; j<=N; j++) {
            if(dp[i][j] == make_pair(-1ll, -1ll)) continue;
            int p = i+j;
            if(!nxt[p]) continue;
            int len = nxt[p] - p;
            if(i + len <= N) {
                dp[i+len][j] = {i, j};
            }
            if(j + len <= N) {
                dp[i][j+len] = {i, j};
            }
        }
    }
    if(dp[N][N].first == -1) 
        return !(cout << -1);
    vector<int> ans1, ans2;
    int i = N, j = N;
    while(!(!i && !j)) {
        auto [ni, nj] = dp[i][j];
        for(int t=i-1; t>=ni; t--) {
            int idx = t+j;
            ans1.push_back(A[idx]);
        }
        for(int t=j-1; t>=nj; t--) {
            int idx = i+t;
            ans2.push_back(A[idx]);
        }
        i = ni;
        j = nj;
    }
    reverse(all(ans1));
    reverse(all(ans2));
    for(int a: ans1)
        cout << a << ' ';
    cout << '\n';
    for(int b: ans2)
        cout << b << ' ';
}
