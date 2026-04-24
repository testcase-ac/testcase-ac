#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 3e5+1;
int pre_x_mx[MX], pre_x_mn[MX], post_x_mx[MX], post_x_mn[MX];
struct point {
    int x, y;
    bool operator<(const point& p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
};
bool solve(vector<point> &v, int m) {
    for(int l=0, r=0; l<v.size(); l++) {
        while(r < v.size() && v[r].y - v[l].y <= m) {
            r++;
        }
        int x_mx = max(l ? pre_x_mx[l - 1] : 0, r < v.size() ? post_x_mx[r] : 0);
        int x_mn = min(l ? pre_x_mn[l - 1] : 2e9, r < v.size() ? post_x_mn[r] : 2e9);
        if(x_mx - x_mn <= m) {
            return true;
        }
    }
    return false;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<point> v(N);
    for(int i=0; i<N; i++) {
        cin >> v[i].x >> v[i].y;
    }
    int l = 0, r = 2e9;
    sort(v.begin(), v.end(), [](const point& a, const point& b) {
        return a.y < b.y;
    });
    pre_x_mx[0] = pre_x_mn[0] = v[0].x;
    for(int i=1; i<N; i++) {
        pre_x_mx[i] = max(pre_x_mx[i-1], v[i].x);
        pre_x_mn[i] = min(pre_x_mn[i-1], v[i].x);
    }
    post_x_mx[N-1] = post_x_mn[N-1] = v[N-1].x;
    for(int i=N-2; i>=0; i--) {
        post_x_mx[i] = max(post_x_mx[i+1], v[i].x);
        post_x_mn[i] = min(post_x_mn[i+1], v[i].x);
    }

    while(l < r) {
        int m = (l + r) / 2;
        if(solve(v, m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << fixed << setprecision(1) << l / 2.0 << '\n';
}
