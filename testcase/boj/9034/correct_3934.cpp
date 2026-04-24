#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()
struct op {
    char c;
    int j, k;
};
void solve() {
    int N, M;
    cin >> N >> M;
    vector<op> ops(M);
    vector<int> scores(N+1);
    map<int, int> comp = {{0, 0}};
    for(auto &o: ops) {
        cin >> o.c;
        if(o.c == 'R') {
            cin >> o.j >> o.k;
            scores[o.j] += o.k;
            comp[scores[o.j]] = 0;
        } else {
            cin >> o.j;
        }
        o.j--;
    }
    int nxt = 0;
    for(auto &pr: comp) {
        pr.second = nxt++;
    }
    int SMAX = comp.size();
    vector<int> seg(SMAX * 2);
    auto update = [&](int i, int d) {
        i += SMAX;
        seg[i] += d;
        while(i /= 2) {
            seg[i] = seg[i*2] + seg[i*2+1];
        }
    };
    auto query = [&](int l, int r) {
        l += SMAX, r += SMAX;
        int res = 0;
        while(l < r) {
            if(l&1) res += seg[l++];
            if(r&1) res += seg[--r];
            l /= 2, r /= 2;
        }
        return res;
    };
    fill(all(scores), 0ll);
    update(0, N);
    for(auto &o: ops) {
        if(o.c == 'R') {
            int old = comp[scores[o.j]];
            update(old, -1);
            scores[o.j] += o.k;
            int nww = comp[scores[o.j]];
            update(nww, 1);
            // printf("update from %d -> %d\n", old, nww);
        } else {
            
            int upper = query(comp[scores[o.j]] + 1, SMAX);
            // printf("query on %d - %d, got %d\n", comp[scores[o.j]] + 1, SMAX, upper);
            cout << upper + 1 << '\n';
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
}
