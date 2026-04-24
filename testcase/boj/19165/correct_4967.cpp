#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>

const int H = 17;
const int MX = 1 << H;
const int MOD = 1000000007;
struct elem {
    int x1, y1, x2, y2;
};

elem combine(elem l, elem r) {
    int x1 = l.x1 * r.x1 + l.x2 * r.y1;
    int y1 = l.y1 * r.x1 + l.y2 * r.y1;
    int x2 = l.x1 * r.x2 + l.x2 * r.y2;
    int y2 = l.y1 * r.x2 + l.y2 * r.y2;
    return {x1 % MOD, y1 % MOD, x2 % MOD, y2 % MOD};
}
elem seg[MX * 2];
int delay[MX], n;
elem rev(elem &t) {
    return {t.y2, t.x2, t.y1, t.x1};
}
void apply(int p) {
    seg[p] = rev(seg[p]);
    if(p < MX)
        delay[p] ^= 1;
}
void build(int p) {
    while(p) {
        p /= 2;
        seg[p] = combine(seg[p * 2], seg[p * 2 + 1]);
        if(delay[p])
            seg[p] = rev(seg[p]);
    }
}
void push(int p) {
    for(int s = H; s; s--) {
        int i = p >> s;
        if(delay[i]) {
            apply(i * 2);
            apply(i * 2 + 1);
            delay[i] = 0;
        }
    }
}
void update(int l, int r) {
    l += MX, r += MX;
    int l0 = l, r0 = r;
    while(l < r) {
        if(l & 1)
            apply(l++);
        if(r & 1)
            apply(--r);
        l /= 2, r /= 2;
    }
    build(l0);
    build(r0 - 1);
}
elem query(int l, int r) {
    l += MX, r += MX;
    push(l);
    push(r - 1);
    elem resl = {1, 0, 0, 1}, resr = {1, 0, 0, 1};
    while(l < r) {
        if(l & 1)
            resl = combine(resl, seg[l++]);
        if(r & 1)
            resr = combine(seg[--r], resr);
        l /= 2, r /= 2;
    }
    return combine(resl, resr);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'A') {
            seg[i + MX] = {1, 1, 0, 1};
        } else {
            seg[i + MX] = {1, 0, 1, 1};
        }
    }
    for(int i = MX - 1; i; i--) {
        seg[i] = combine(seg[i * 2], seg[i * 2 + 1]);
    }
    while(q--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        if(t == 1) {
            update(l, r);
        } else {
            int a, b;
            cin >> a >> b;
            elem e = query(l, r);
            int at = (e.x1 * a + e.y1 * b) % MOD, bt = (e.x2 * a + e.y2 * b) % MOD;
            cout << at << ' ' << bt << '\n';
        }
    }
}
