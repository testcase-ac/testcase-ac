#include <bits/stdc++.h>
using namespace std;
const int MX = 5005;
string arr[MX];
int N, W;
// 2113
int dp[MX], prv[MX];
bool chk(int mx_h) {
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for(int i=1; i<=N; i++) {
        int mx = arr[i].size();
        for(int j=i; j>=max(1, i-mx_h+1); j--) {
            mx = max(mx, (int)arr[j].size());
            if(dp[i] > dp[j-1] + mx) {
                dp[i] = dp[j-1]+mx+1;
                prv[i] = j-1;
            }
        }
    }
    return dp[N] <= W+1;
} 
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> W;
    for(int i=1; i<=N; i++) {
        cin >> arr[i];
    }
    int l = 1, r = N;
    while(l < r) {
        int m = (l+r)/2;
        if(chk(m)) {
            r = m;
        } else {
            l = m+1;
        }
    }
    vector<vector<string>> ans;
    vector<int> ans_c;
    chk(l);
    int cur = N;
    while(cur) {
        ans.emplace_back();
        int mx = 0;
        for(int i=prv[cur]+1; i<=cur; i++) {
            ans.back().push_back(arr[i]);
            mx = max(mx, (int)arr[i].size());
        }
        ans_c.push_back(mx);
        cur = prv[cur];
    }
    reverse(ans.begin(), ans.end());
    reverse(ans_c.begin(), ans_c.end());
    cout << l << ' ' << ans.size() << '\n';
    for(int t: ans_c) {
        cout << t << ' ';
    }
    cout << '\n';
    for(int r=0; r<l; r++) {
        for(int c=0; c<ans_c.size(); c++) {
            if(ans[c].size() > r) {
                cout << ans[c][r];
                int rm = ans_c[c] - ans[c][r].size() + 1;
                while(rm--) {
                    cout << ' ';
                }
            } else {
                int rm = ans_c[c] +1;
                while(rm--)
                    cout << ' ';
            }
        }
        cout << '\n';
    }
}
