#include <bits/stdc++.h>
using namespace std;
const int MX = 100001;
pair<int, int> adj[MX];
vector<int> dv, v;
int mn = MX, mx = 0;
void dfs(int i, int d) {
    if(i == -1) {
        dv.push_back(d);
        mn = min(mn, d);
        mx = max(mx, d);
        return;
    }
    dfs(adj[i].first, d + 1);
    dfs(adj[i].second, d + 1);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> adj[i].first >> adj[i].second;
    }
    dfs(1, 0);
    if(mn == mx) {
        return !(cout << 0);
    }
    if(mn + 1 != mx) {
        return !(cout << -1);
    }
    bool pv = 0;
    for(int t: dv) {
        if(t == mn) {
            v.push_back(0);
        } else {
            if(pv) {
                v.push_back(1);
                pv = 0;
            } else {
                pv = 1;
            }
        }
    }
    // for(int t: v) {
    //     cout << t;
    // }
    // cout << '\n';

    int ans = 0;
    while(v.size() > 1) {
        int len = v.size();
        int cnt = 0;
        bool lft_all = 1, lft_none = 1, rht_all = 1, rht_none = 1;
        for(int i = 0; i < len; i++) {
            if(i < len / 2) {
                if(v[i] == 1) {
                    lft_none = 0;
                } else {
                    lft_all = 0;
                }
            } else {
                if(v[i] == 1) {
                    rht_none = 0;
                } else {
                    rht_all = 0;
                }
            }
            if(v[i]) {
                cnt++;
            }
        }
        if(cnt == 0 || cnt == len) {
            return !(cout << ans);
        }

        if(cnt >= len / 2) {  // lft should be all
            if(lft_all) {
                v.erase(v.begin(), v.begin() + len / 2);
            } else if(rht_all) {
                ans++;
                v.erase(v.begin() + len / 2, v.end());
            } else {
                return !(cout << -1);
            }
        } else {  // rht should be none
            if(lft_none) {
                ans++;
                v.erase(v.begin(), v.begin() + len / 2);
            } else if(rht_none) {
                v.erase(v.begin() + len / 2, v.end());
            } else {
                return !(cout << -1);
            }
        }
    }
    cout << ans;
}
