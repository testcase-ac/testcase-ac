#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1 << 17;
int seg[MX * 2];
int find_kth(int k) {
    int p = 1;
    while(p < MX) {
        if(seg[2 * p + 1] >= k) {
            p = 2 * p + 1;
        } else {
            k -= seg[2 * p + 1];
            p = 2 * p;
        }
    }
    return p - MX;
}
void update(int p, int diff) {
    p += MX;
    seg[p] += diff;
    p /= 2;
    while(p) {
        seg[p] = seg[2 * p] + seg[2 * p + 1];
        p /= 2;
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int> c(n), w(m), b(m);
    for(int i = 0; i < n; i++) {
        cin >> c[i];
        update(c[i], 1);
    }
    for(int i = 0; i < m; i++) cin >> w[i];
    for(int i = 0; i < m; i++) cin >> b[i];
    for(int i = 0; i < m; i++) {
        int k = find_kth(b[i]);
        if(k < w[i]) {
            return !(cout << 0);
        }
        update(k, -1);
        update(k - w[i], 1);
    }
    cout << 1;
}
