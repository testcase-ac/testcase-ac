#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int N, L;
        cin >> N >> L;
        vector<int> v(N), pos(N);
        for(int i=0; i<N; i++) {
            cin >> v[i];
        }
        for(int i=0; i<N; i++) {
            int t;
            cin >> t;
            pos[t-1] = i;
        }
        bool ans = 1;
        int l = 0, r = 0;
        set<int> st;
        for(int i=0; i<N; i++) {
            while(r < N && v[r] <= v[i] + L) {
                st.insert(pos[r++]);
            }
            while(l < N && v[l] < v[i] - L) {
                st.erase(pos[l++]);
            }
            if(*st.rbegin() - *st.begin() + 1 != st.size()) {
                ans = 0;
                break;
            }
        }
        cout << (ans ? 1 : -1) << '\n';
    }
}
