#include <bits/stdc++.h>
using namespace std;
#define int long long
pair<double, double> p[101];
struct edge {
    int u, v;
    double w;
    bool operator<(const edge &o) const {
        return w < o.w;
    }
};
int dsu[101];
int find(int x) {
    if(dsu[x] == x) return x;
    return dsu[x] = find(dsu[x]);
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
    }
    vector<edge> edges;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            double d = hypot(p[i].first - p[j].first, p[i].second - p[j].second);
            edges.push_back({i, j, d});
        }
    }
    sort(edges.begin(), edges.end());
    double ans = 0;
    for(auto [u, v, w]: edges) {
        int x = find(u);
        int y = find(v);
        if(x != y) {
            ans += w;
            dsu[x] = y;
        }
    }
    cout << ans;
}
