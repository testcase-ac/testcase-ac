#include <bits/stdc++.h>
using namespace std;
struct rect {
    int r1, r2, c1, c2;
    void read() {
        cin >> r1 >> c2 >> r2 >> c1;
    }
};
const int H = 20, MX = 1000000;
rect arr[100000];
vector<pair<int, int>> r1v[MX], r2v[MX];
const int SEGMX = 1 << H;
int seg[SEGMX * 2], lazy[SEGMX];
void apply(int p, int val) {
    seg[p] += val;
    if(p < SEGMX) {
        lazy[p] += val;
    }
}
void build(int p) {
    while(p > 1) {
        p >>= 1;
        seg[p] = max(seg[p << 1], seg[p << 1 | 1]) + lazy[p];
    }
}
void push(int p) {
    for(int s = H; s >= 0; s--) {
        int i = p >> s;
        if(lazy[i]) {
            apply(i << 1, lazy[i]);
            apply(i << 1 | 1, lazy[i]);
            lazy[i] = 0;
        }
    }
}
void inc(int l, int r, int v) {
    l += SEGMX, r += SEGMX;
    int l0 = l, r0 = r;
    for(; l < r; l >>= 1, r >>= 1) {
        if(l & 1) apply(l++, v);
        if(r & 1) apply(--r, v);
    }
    build(l0), build(r0 - 1);
}

int query() {
    return seg[1];
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int _, K, N;
    cin >> _ >> _ >> _ >> _;
    cin >> K >> N;
    for(int i = 0; i < N; i++) {
        arr[i].read();
        r1v[arr[i].r1].push_back({arr[i].c1, arr[i].c2});
        r2v[arr[i].r2].push_back({arr[i].c1, arr[i].c2});
    }
    int ans = 0;
    for(int i = -K; i < MX - K; i++) {
        int j = i + K;
        for(auto [c1, c2]: r2v[j]) {
            int cl = max(c2 - K, 0), cr = c1;
            inc(cl, cr + 1, 1);
        }
        ans = max(ans, query());
        if(i >= 0) {
            for(auto [c1, c2]: r1v[i]) {
                int cl = max(c2 - K, 0), cr = c1;
                inc(cl, cr + 1, -1);
            }
        }
    }
    cout << ans;
}
