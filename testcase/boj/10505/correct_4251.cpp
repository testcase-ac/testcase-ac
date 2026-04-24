#include <bits/stdc++.h>
using namespace std;
#define int long long
struct circle {
    int x, y, r;
    void read() {cin >> x >> y >> r;}
};
struct frac {
    int a, b;
    void simplify() {
        int g = gcd(a, b);
        a /= g, b /= g;
    }
    frac mult(frac f) {
        frac res = {a * f.a, b * f.b};
        res.simplify();
        return res;
    }
};
bool intersect(circle a, circle b) {
    int xx = abs(a.x - b.x), yy = abs(a.y - b.y), rr = a.r + b.r;
    xx *= xx;
    yy *= yy;
    rr *= rr;
    return xx + yy == rr;
}
vector<vector<int>> adj;
vector<circle> v;
bool dir[1001];
frac ans[1001];
void dfs(int i, int p) {
    for(int a: adj[i]) {
        if(a == p || ans[a].b) continue;
        ans[a] = ans[i].mult(frac{v[i].r, v[a].r});
        dir[a] = !dir[i];
        dfs(a, i);
    }
}
void solve() {
    int N;
    cin >> N;
    v = vector<circle>(N);
    memset(dir, 0, sizeof(bool) * N);
    memset(ans, 0, sizeof(frac) * N);
    for(auto &t: v) t.read();
    adj.resize(N);
    for(int i=0; i<N; i++) {
        adj[i].clear();
    }
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) {
            if(intersect(v[i], v[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    ans[0] = {1,1};
    dfs(0, -1);
    for(int i=0; i<N; i++) {
        if(!ans[i].b) {
            cout << "not moving\n";
            continue;
        }
        if(ans[i].b == 1) {
            cout << ans[i].a << ' ';
        } else {
            cout << ans[i].a << '/' << ans[i].b << ' ';
        }
        if(dir[i]) {
            cout << "counterclockwise\n";
        } else {
            cout << "clockwise\n";
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}
