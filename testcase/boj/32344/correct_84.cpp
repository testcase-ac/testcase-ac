#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C, N;
    cin >> R >> C >> N;
    vector<vector<pair<int, int>>> arr(N+1);
    for(int i=0; i<=N; i++) {
        int a, v, h;
        cin >> a >> v >> h;
        arr[a].push_back({v, h});
    }
    int mx_sz = 0, mx_i = 0;
    for(int i=1; i<=N; i++) {
        if(!arr[i].size()) continue;
        int rmin = INT_MAX, rmax = INT_MIN, cmin = INT_MAX, cmax = INT_MIN;
        for(auto [v, h] : arr[i]) {
            rmin = min(rmin, v);
            rmax = max(rmax, v);
            cmin = min(cmin, h);
            cmax = max(cmax, h);
        }
        int sz = (rmax - rmin + 1) * (cmax - cmin + 1);
        if(sz > mx_sz) {
            mx_sz = sz;
            mx_i = i;
        }
    }
    cout << mx_i << ' ' << mx_sz;
}
