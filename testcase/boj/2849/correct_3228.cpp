#include <bits/stdc++.h>
using namespace std;
#define int long long

const int H = 18;
const int MX = 1 << H;
struct node {
    int lans, mans, rans, len;
    bool lch, rch;
};
node combine(node const& l, node const& r) {
    node res;
    res.lans = l.lans;
    if(l.lans == l.len && l.rch != r.lch) {
        res.lans += r.lans;
    }
    res.rans = r.rans;
    if(r.rans == r.len && r.lch != l.rch) {
        res.rans += l.rans;
    }
    res.mans = max({l.lans, l.mans, l.rans, r.lans, r.mans, r.rans, res.lans, res.rans});
    if(l.rch != r.lch) {
        res.mans = max(res.mans, l.rans + r.lans);
    }
    res.lch = l.lch;
    res.rch = r.rch;
    res.len = l.len + r.len;
    return res;
}
node t[MX * 2];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        t[i + MX].lans = t[i + MX].rans = t[i + MX].mans = t[i + MX].len = 1;
    }
    for(int i = MX - 1; i; i--) {
        t[i] = combine(t[i << 1], t[i << 1 | 1]);
    }
    while(q--) {
        int p;
        cin >> p;
        p--;
        p += MX;
        t[p].lch = t[p].rch = !t[p].lch;
        p /= 2;
        while(p) {
            t[p] = combine(t[p << 1], t[p << 1 | 1]);
            p /= 2;
        }
        cout << t[1].mans << '\n';
    }
}
