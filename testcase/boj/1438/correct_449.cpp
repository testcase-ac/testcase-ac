#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
struct point {
    int x, y;
    void read() {cin >> x >> y;}
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    if(N == 2) {
        return !(cout << 4);
    }
    vector<point> v(N);
    vector<int> ys;
    for(auto &t: v) {
        t.read();
        ys.push_back(t.y);
    }
    sort(all(ys));
    ys.erase(unique(all(ys)), ys.end());
    int ans = INT_MAX;
    for(int i1=0; i1<ys.size(); i1++) {
        for(int i2=0; i2<ys.size(); i2++) {
            int y_lo = ys[i1], y_hi = ys[i2];
            vector<int> xs;
            for(auto [x, y]: v) {
                if(y < y_lo || y > y_hi) {
                    continue;
                }
                xs.push_back(x);
            }
            sort(all(xs));
            int ptr = 0;
            for(int t=0; t+N/2-1<xs.size(); t++) {
                int te = t+N/2-1;
                int x_lo = xs[t], x_hi = xs[te];
                ans = min(ans, (x_hi - x_lo + 2) * (y_hi - y_lo + 2));
            }
        }
    }
    cout << ans;
}
