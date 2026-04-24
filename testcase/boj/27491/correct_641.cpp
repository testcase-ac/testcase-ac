#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) x.begin(), x.end()
const int MX = 2e5+2;
int seg[MX*2];
void update(int i, int v) {
    // printf("updated %d %d\n", i, v);
    i += MX;
    seg[i] = v;
    while(i /= 2) {
        seg[i] = max(seg[i*2], seg[i*2+1]);
    }
}
int query(int l, int r) {
    int res = -MX;
    l += MX, r += MX;
    while(l < r) {
        if(l&1) res = max(res, seg[l++]);
        if(r&1) res = max(res, seg[--r]);
        l /= 2, r /= 2;
    }
    return res;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    fill(seg, seg+MX*2, -MX);
    int N;
    cin >> N;
    vector<int> v(N), accs = {0};
    int csum = 0;
    for(int i=0; i<N; i++) {
        cin >> v[i];
        csum += v[i];
        accs.push_back(csum);
    }
    sort(all(accs));
    csum = 0;
    int idx = lower_bound(all(accs), csum) - accs.begin();
    update(idx, 1);
    int prv_dp = 0;
    for(int i=0; i<N; i++) {
        csum += v[i];
        int dp = prv_dp;
        idx = lower_bound(all(accs), csum) - accs.begin();
        int res = query(0, idx+1);
        // printf("at i = %d, csum = %d, idx = %d, res = %d\n", i, csum, idx, res);
        dp = max(dp, res+i);
        update(idx, dp-i);
        prv_dp = dp;
    }
    cout << prv_dp;
}