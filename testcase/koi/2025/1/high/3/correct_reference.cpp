#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
 
int tree[1048576], lazy[1048576];
 
void propagate(int i, int b, int e) {
    if (b < e) for (int j: { i * 2 + 1, i * 2 + 2 }) lazy[j] += lazy[i];
    tree[i] += lazy[i];
    lazy[i] = 0;
}
 
int update(int i, int b, int e, int l, int r, int v) {
    propagate(i, b, e);
    if (r < b || e < l) return tree[i];
    if (l <= b && e <= r) {
        lazy[i] += v;
        propagate(i, b, e);
        return tree[i];
    }
    int m = (b + e) / 2;
    return tree[i] = min(update(i * 2 + 1, b, m, l, r, v), update(i * 2 + 2, m + 1, e, l, r, v));
}
 
int query(int i, int b, int e, int l, int r) {
    propagate(i, b, e);
    if (r < b || e < l) return (int)1e9;
    if (l <= b && e <= r) return tree[i];
    int m = (b + e) / 2;
    return min(query(i * 2 + 1, b, m, l, r), query(i * 2 + 2, m + 1, e, l, r));
}
 
int n, q;
vector<pair<int, int>> adj[200006];
vector<pair<pair<long long, long long>, int>> queries;
int par[200006], path[200006], sp[20][200006];
long long dist[20][200006], depth[200006];
vector<long long> compress;
 
void dfs(int x, int prev = -1) {
    par[x] = prev;
    sp[0][x] = prev;
    for (auto &[ i, j ]: adj[x]) {
        if (i != prev) {
            depth[i] = depth[x] + j;
            dfs(i, x);
            dist[0][i] = j;
        }
    }
}
 
pair<int, long long> reduction(int a, long long b) {
    for (int t = 19; t >= 0; t--) {
        if (sp[t][a] == -1 || path[sp[t][a]]) continue;
        b -= dist[t][a];
        a = sp[t][a];
    }
    if (!path[a]) {
        b -= dist[0][a];
        a = sp[0][a];
    }
    return { a, b };
}
 
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--, v--;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }
    for (int t = 0; t < 20; t++) for (int i = 0; i < n; i++) {
        sp[t][i] = -1;
        dist[t][i] = (long long)1e18;
    }
    depth[0] = 0;
    dfs(0);
    for (int t = 1; t < 20; t++) for (int i = 0; i < n; i++) {
        if (sp[t - 1][i] == -1) {
            sp[t][i] = -1;
            dist[t][i] = (long long)1e18;
        } else {
            sp[t][i] = sp[t - 1][sp[t - 1][i]];
            dist[t][i] = min((long long)1e18, dist[t - 1][i] + dist[t - 1][sp[t - 1][i]]);
        }
    }
    for (int i = 0; i < n; i++) path[i] = 0;
    path[0] = 1;
    for (int i = n - 1; i != 0; i = par[i]) path[i] = 1;
    for (int i = 0; i < q; i++) {
        int t, x;
        long long y;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%lld", &x, &y);
            x--;
            auto [ a, b ] = reduction(x, y);
            queries.push_back({ { depth[a] - b, depth[a] + b }, 1 });
        } else {
            scanf("%d", &x);
            x--;
            queries.push_back({ queries[x].first, -1 });
        }
    }
    compress.push_back(depth[0]);
    compress.push_back(depth[n - 1]);
    for (auto &[ i, j ]: queries) {
        compress.push_back(i.first);
        compress.push_back(i.second);
    }
    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());
    for (auto &[ i, j ]: queries) {
        i.first = lower_bound(compress.begin(), compress.end(), i.first) - compress.begin();
        i.second = upper_bound(compress.begin(), compress.end(), i.second - 1) - compress.begin() - 1;
    }
    int fi = lower_bound(compress.begin(), compress.end(), depth[0]) - compress.begin();
    int se = lower_bound(compress.begin(), compress.end(), depth[n - 1]) - compress.begin() - 1;
    for (auto &[ i, j ]: queries) {
        update(0, 0, 524287, i.first, i.second, j);
        puts(query(0, 0, 524287, fi, se) ? "YES" : "NO");
    }
}
