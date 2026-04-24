#include <bits/stdc++.h>
using namespace std;
struct point {
    int x, y;
    point operator-(point a) {
        return {x - a.x, y - a.y};
    }
    int cross(point p) {
        return x * p.y - y * p.x;
    }
    int dist() {
        return x * x + y * y;
    }
};
int ccw(point A, point B, point C) {
    int c = (B - A).cross(C - B);
    if(c > 0)
        return 1;  // ccw
    else if(c < 0)
        return -1;  // cw
    else
        return 0;  // colinear
}
void build_chull(vector<point>& arr, vector<point>& chull) {
    int n = arr.size();
    if(n <= 2) {
        chull = arr;
        return;
    }
    auto it = min_element(arr.begin(), arr.end(), [](point& a, point& b) {
        return tie(a.y, a.x) < tie(b.y, b.x);
    });
    swap(arr[0], *it);
    sort(arr.begin() + 1, arr.end(), [&arr](point& a, point& b) {
        int o = ccw(arr[0], a, b);
        if(o)
            return o > 0;
        else
            return (arr[0] - a).dist() < (arr[0] - b).dist();
    });
    chull = {arr[0], arr[1]};
    for(int i = 2; i < n; i++) {
        while(chull.size() >= 2 && ccw(chull[chull.size() - 2], chull[chull.size() - 1], arr[i]) != 1)
            chull.pop_back();
        chull.push_back(arr[i]);
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, L;
    cin >> N >> L;
    vector<point> points, chull;
    for(int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back({x, y});
    }
    build_chull(points, chull);
    double ans = 0;
    for(int i = 0; i < chull.size(); i++) {
        int j = (i + 1) % chull.size();
        point p = chull[i] - chull[j];
        ans += sqrt(p.dist());
    }
    ans += M_PI * 2 * L;
    cout << fixed << setprecision(0) << ans << '\n';
}
