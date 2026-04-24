#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()

struct point {
    int x, y, v, w, val;
};
int dst(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
int see_time(int v, int w, int arrive) {
    if(arrive <= v) {
        return w-v;
    } else if(arrive >= w) {
        return 0;
    } else {
        return w - arrive;
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<point> v(N);
    for(auto &t: v) {
        cin >> t.x >> t.y;
    }
    for(auto &t: v) {
        cin >> t.v >> t.w;
    }
    v.push_back({0,0,0,0,0});
    int ans = 0;
    sort(all(v), [&](point &a, point &b){return a.w < b.w;});
    for(int i=1; i<N+1; i++) {
        auto &p = v[i];
        p.val = INT_MIN;
        for(int j=0; j<i; j++) {
            int d = dst(p.x, p.y, v[j].x, v[j].y);
            int arrive = v[j].w + d;
            if(arrive > p.w) continue;
            p.val = max(p.val, v[j].val + see_time(p.v, p.w, arrive));
        }
        ans = max(ans, p.val);
    }
    cout << ans;
}
