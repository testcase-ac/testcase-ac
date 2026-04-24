#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> v(N), ans(N), freq(1000001);
    vector<vector<pair<int, int>>> buk(1000001);
    for(int i=0; i<N; i++) {
        cin >> v[i];
        freq[v[i]]++;
    }
    for(int i=0; i<N; i++) {
        buk[freq[v[i]]].push_back({i, v[i]});
    }
    set<pair<int, int>> st;
    for(int f=1000000; f>=1; f--) {
        for(auto [idx, num]: buk[f]) {
            auto it = st.lower_bound(make_pair(idx, num));
            if(it == st.end()) {
                ans[idx] = -1;
            } else {
                ans[idx] = it->second;
            }
            st.insert({idx, num});
        }
    }
    for(int a: ans) {
        cout << a << ' ';
    }
}
