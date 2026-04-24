#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
    int s, q, i;
    bool operator<(const node &o) const {
        return q < o.q;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, W;
    cin >> N >> W;
    vector<node> v(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i].s >> v[i].q;
        v[i].i = i;
    }
    sort(v.begin(), v.end(), [](node a, node b) {
        return a.s * b.q < b.s * a.q;
    });
    multiset<node> st;
    int sm = 0, ansi = 0, ans = 0, ansx = 1e14, ansy = 1;
    for(node t: v) {
        int q_sum = W * t.q / t.s;
        st.insert(t);
        sm += t.q;
        while(sm > q_sum) {
            sm -= st.rbegin()->q;
            st.erase(prev(st.end()));
        }
        int newx = sm * t.s, newy = t.q;
        if(ans < st.size() || (ans == st.size() && ansx * newy > newx * ansy)) {
            ans = st.size();
            ansi = t.i;
            ansx = newx;
            ansy = newy;
        }
    }

    st.clear();
    sm = 0;
    for(node t: v) {
        int q_sum = W * t.q / t.s;
        st.insert(t);
        sm += t.q;
        while(sm > q_sum) {
            sm -= st.rbegin()->q;
            st.erase(prev(st.end()));
        }
        if(t.i == ansi) {
            cout << st.size() << '\n';

            vector<node> aa(st.begin(), st.end());
            sort(aa.begin(), aa.end(), [](node a, node b) {
                return a.i < b.i;
            });
            for(node &k: aa) {
                cout << k.i + 1 << '\n';
            }
        }
    }
}
