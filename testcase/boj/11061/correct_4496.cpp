#include <bits/stdc++.h>
using namespace std;
#define int long long
struct info {
    int x, y, close;
    bool operator<(const struct info& i) const {
        return close < i.close;
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<info> v;
        vector<int> par(n), sz(n), edge_sz(n);
        function<int(int)> f = [&](int i) {
            return par[i] == i ? i : par[i] = f(par[i]);
        };
        auto join = [&](int i, int j) {
            int x = f(i), y = f(j);
            if(x != y) {
                par[x] = y;
                sz[y] += sz[x];
                edge_sz[y] += edge_sz[x];
            }
            edge_sz[y]++;
        };
        for(int i=0; i<n; i++) {
            par[i] = i;
            sz[i] = 1;
            edge_sz[i] = 0;
            for(int j=i+1; j<n; j++) {
                int w;
                cin >> w;
                v.push_back({i, j, w});
            }
        }
        sort(v.begin(), v.end());
        int ans = 0;
        for(int i=0, j=0; i<v.size(); i=j) {
            while(j < v.size() && v[i].close == v[j].close) {
                join(v[j].x, v[j].y);
                j++;
            }
            for(int t=i; t<j; t++) {
                int x = f(v[t].x);
                if(sz[x] * (sz[x] - 1) / 2 == edge_sz[x] && sz[x] != n) {
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }
    
}
