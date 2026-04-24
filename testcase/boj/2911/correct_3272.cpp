#include <bits/stdc++.h>
using namespace std;
#define int long long

struct point {
    int p, c;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<point> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].p >> v[i].c;
    }
    int t = 0, ans = 0;
    sort(v.begin(), v.end(), [](point &a, point &b) {
        return a.p < b.p;
    });
    for(auto p: v) {
        if(t < p.c) {
            ans += p.c - t;
        }
        t = p.c;
    }
    cout << ans;
}
