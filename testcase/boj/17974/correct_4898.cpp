#include <bits/stdc++.h>
using namespace std;
struct info {
    int l, r, v;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M, N;
    cin >> M >> N;
    vector<int> colors(N), pos(N), dp(N);
    for(int i = 0; i < N; i++) {
        cin >> pos[i];

    }
    for(int i = 0; i < N; i++) {
        cin >> colors[i];

    }
    int i;
    for(i=0; i<N && colors[i] == colors[0]; i++) {
        dp[i] = 1;
    }
    for(int t=i; i<N; i=t) {
        int gmin = 1e9;
        multiset<int> st;
        vector<info> v;
        for(int x=i-1; x>=0 && colors[x] == colors[i-1]; x--) {
            int a = pos[i-1] - pos[x], b = pos[i] - pos[x];
            v.push_back({pos[x] + a*2, pos[x] + b*2, dp[x]});
        }
        int l = 0, r = 0;
        int lst = 0;
        while(t < N && colors[i] == colors[t]) {
            while(r < v.size() && v[r].l <= pos[t]) {
                st.insert(v[r].v);
                r++;
            }
            while(l < v.size() && v[l].r < pos[t]) {
                st.erase(st.find(v[l].v));
                l++;
            }

            if(lst < l) {
                lst = l;
            }
            while(lst < r) {
                gmin = min(gmin, v[lst].v);
                lst++;
            }
            dp[t] = gmin + 2;
            if(st.size()) {
                dp[t] = min(dp[t], *st.begin() + 1);
            }
            t++;
        }
    }
    int ans = dp[N-1];
    i = N-1;
    while(i >= 0 && colors[i] == colors[N-1]) {
        ans = min(ans, dp[i]);
        i--;
    }
    cout << ans;
}
