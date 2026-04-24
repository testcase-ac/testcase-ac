#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    int h, lst, x;
    cin >> lst;
    vector<pair<int,int>> pts;
    pts.push_back({lst, 0});
    for(int i=1; i<2*n; i++) {
        int cur;
        cin >> cur;
        if(i % 2 == 1) {
            pts.push_back({cur, pts.back().second + (cur - lst)});
        } else {
            pts.push_back({cur, pts.back().second - (cur - lst)});
        }
        lst = cur;
    }
    cin >> x;
    int t = lower_bound(pts.begin(), pts.end(), make_pair(x, 0ll)) - pts.begin();
    int grad = (pts[t].second - pts[t-1].second) / (pts[t].first - pts[t-1].first);
    int y = pts[t].second - grad * (pts[t].first - x);
    // printf("x = %lld, y = %lld\n", x, y);
    int ans = 0;
    for(int i=1; i<2*n; i+=2) {
        if(pts[i].first >= x) break;
        int ty = (pts[i].second - y), tx = (x - pts[i].first);
        // printf("tx = %lld, ty = %lld, y = %lld\n", tx, ty, y);
        double cur_y = ty / 1. / tx * x + y;
        // printf("cur_y = %lf\n", cur_y);
        ans = max(ans, (int)round(cur_y + 0.5 - 1e-9));
    }
    cout << ans;
}
