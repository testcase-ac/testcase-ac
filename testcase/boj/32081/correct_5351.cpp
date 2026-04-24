#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
struct info {
    int v, lv, rv, sum;
};

info mrg(info l, info r) {
    info cur;
    cur.v = max({l.v, r.v, l.rv+r.lv});
    cur.lv = max(l.lv, l.sum+r.lv);
    cur.rv = max(r.rv, r.sum+l.rv);
    cur.sum = l.sum + r.sum;

    return cur;
}
const int MX = 1e5+3;
info seg[MX*2];
void seg_update(int i, int v) {
    i += MX;
    seg[i] = {seg[i].v+v,seg[i].v+v,seg[i].v+v,seg[i].v+v};
    while(i /= 2) {
        seg[i] = mrg(seg[i*2], seg[i*2+1]);
    }
}
info seg_query(int l, int r) {
    info lft = {-MX,-MX,-MX,-MX}, rht = {-MX,-MX,-MX,-MX};
    l += MX, r += MX;
    while(l < r) {
        if(l&1) lft = mrg(lft, seg[l++]);
        if(r&1) rht = mrg(seg[--r], rht);
        l /= 2, r /= 2;
    }
    return mrg(lft, rht);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, Q;
    cin >> N >> M;
    vector<vector<pair<int, int>>> buk(N+2);
    rep(i, M) {
        int l, r, x;
        cin >> l >> r >> x;
        buk[l].push_back({i, x});
        buk[r+1].push_back({i, -x});
    }
    cin >> Q;
    vector<int> ans(Q);
    vector<vector<tuple<int, int, int>>> query_buk(N+1);
    rep(i, Q) {
        int k, s, t;
        cin >> k >> s >> t;
        query_buk[k].push_back({i, s, t});
    }
    for(int q=1; q<=N; q++) {
        // printf("q = %lld\n", q);
        for(auto [i, x]: buk[q]) {
            seg_update(i, x);
            // printf("  seg update %lld %lld\n", i, x);
        }
        for(auto [qi, s, t]: query_buk[q]) {
            auto res = seg_query(s-1, t);
            ans[qi] = res.v;
            // printf("at query index %lld, qry %lld %lld, res.v = %lld\n", qi, s-1, t, res.v);
        }
    }
    rep(i, Q) {
        cout << ans[i] << '\n';
    }
}
