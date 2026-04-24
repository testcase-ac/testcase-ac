#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K;
    cin >> N >> K;
    vector<int> arr(K);
    map<int, vector<int>> mp;
    for(int i=0; i<K; i++) {
        int t;
        cin >> t;
        arr[i] = t;
        mp[t].push_back(i);
    }
    for(auto &[t, v]: mp) {
        sort(all(v), greater<int>());
    }
    set<pair<int, int>> st;
    auto next_idx = [&](int t) {
        auto &v = mp[t];
        if(v.size() == 0)
            return 0ll;
        else
            return K - v.back();
    };
    int ans = 0;
    for(auto &t: arr) {
        // printf("at t = %d: ", t);
        if(st.count({next_idx(t), t})) {
            // printf("already has t\n");
            st.erase({next_idx(t), t});
            auto &v = mp[t];
            v.pop_back();
            st.insert({next_idx(t), t});
            continue;
        }
        if(st.size() < N) {
            // printf("size ok\n");
            auto &v = mp[t];
            v.pop_back();
            st.insert({next_idx(t), t});
            continue;
        }
        ans++;
        auto &v = mp[t];
        v.pop_back();
        // printf("erase (next idx %d), number %d\n", st.begin()->first, st.begin()->second);
        st.erase(st.begin());
        st.insert({next_idx(t), t});
     }
    cout << ans;
}
