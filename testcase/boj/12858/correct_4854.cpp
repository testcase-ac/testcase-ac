#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node {
    int mx_gcd, diff;
    int get_gcd() {
        return gcd(mx_gcd, diff);
    }
};

node combine(node a, node b) {
    int g = gcd(gcd(a.mx_gcd, b.mx_gcd), abs(a.diff - b.diff));
    return {g, g ? a.diff % g : a.diff};
}

const int H = 17;
const int MX = 1 << H;
node t[MX * 2];
int d[MX];
void apply(int p, int value) {
    t[p].diff = t[p].mx_gcd ? ((t[p].diff + value) % t[p].mx_gcd) : (t[p].diff + value);
    if(p < MX) d[p] += value;
}
void build(int p) {
    while(p) {
        p /= 2;
        t[p] = combine(t[p * 2], t[p * 2 + 1]);
        t[p].diff = t[p].mx_gcd ? ((t[p].diff + d[p]) % t[p].mx_gcd) : (t[p].diff + d[p]);
    }
}
void push(int p) {
    for(int s = H; s; s--) {
        int i = p >> s;
        if(d[i]) {
            apply(i * 2, d[i]);
            apply(i * 2 + 1, d[i]);
            d[i] = 0;
        }
    }
}
void update(int l, int r, int t) {
    l += MX, r += MX;
    int l0 = l, r0 = r;
    while(l < r) {
        if(l & 1) {
            // printf("apply %d to %d\n", t, l);
            apply(l++, t);
        }
        if(r & 1) apply(--r, t);
        l /= 2, r /= 2;
    }
    build(l0);
    build(r0 - 1);
}
node query(int l, int r) {
    node res = {0, 0};
    l += MX, r += MX;
    // printf("at t[1] = %d %d, d[1] = %d\n", t[1].mx_gcd, t[1].diff, d[1]);
    // printf("at t[2] = %d %d, d[2] = %d\n", t[2].mx_gcd, t[2].diff, d[2]);
    push(l);
    push(r - 1);
    while(l < r) {
        if(l & 1)
            res = combine(res, t[l++]);
        if(r & 1)
            res = combine(res, t[--r]);
        l >>= 1, r >>= 1;
    }
    return res;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t[i + MX].diff;
    }
    for(int i = MX - 1; i; i--) {
        t[i] = combine(t[i << 1], t[i << 1 | 1]);
    }
    int q;
    cin >> q;
    while(q--) {
        int t, a, b;
        cin >> t >> a >> b;
        a--;
        if(t) {
            update(a, b, t);
        } else {
            cout << query(a, b).get_gcd() << '\n';
        }
    }
}
