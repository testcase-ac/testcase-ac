#include <bits/stdc++.h>
using namespace std;
#define int long long
struct info {
    int l, r, i;
    bool operator< (info i) {
        return make_pair(l, -r) < make_pair(i.l, -i.r);
    }
};
const int MX = 2e5 + 5;
int seg[MX*4], N, ans[MX];
void update(int t, int v) {
    t += 2*N;
    while(t) {
        seg[t] = max(seg[t], v);
        t /= 2;
    }
}

int query(int l, int r) {
    l += 2*N, r += 2*N;
    int res = -1;
    while(l < r) {
        if(l&1) res = max(res, seg[l++]);
        if(r&1) res = max(res, seg[--r]);
        l /= 2, r /= 2;
    }
    return res;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(seg, -1, sizeof seg);
    cin >> N;
    vector<info> arr(N);
    map<int, int> mp;
    for(int i=0; i<N; i++) {
        int a, t;
        cin >> a >> t;
        mp[a] = 0;
        mp[a+t] = 0;
        arr[i] = {a, a+t, i};
    }
    int idx = 0;
    for(auto &[k, v]: mp) {
        v = idx++;
    }
    for(auto &[l, r, i]: arr) {
        l = mp[l];
        r = mp[r];
    }
    sort(arr.begin(), arr.end());
    for(auto [l, r, i]: arr) {
        int q = query(r, 2*N);
        ans[i] = q+1;
        update(r, ans[i]);
    }
    for(int i=0; i<N; i++) {
        cout << ans[i] << ' ';
    }
}
