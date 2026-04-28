#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct DSU
{
    int n;
    vector<int> par, mn, mx, l, r, sz;

    DSU(int _n) : n(_n), par(_n), mn(_n), mx(_n), l(_n), r(_n), sz(_n, 1)
    {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x)
    {
        while(x != par[x]) x = par[x] = par[par[x]];
        return x;
    }

    bool uni(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        par[b] = a;
        mn[a] = min(mn[a], mn[b]);
        mx[a] = max(mx[a], mx[b]);
        r[a] = max(r[a], r[b]);
        l[a] = min(l[a], l[b]);
        sz[a] += sz[b];
        return true;
    }
};


void solve()
{
    int n;
    cin >> n;

    DSU dsu(n);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        dsu.mn[i] = a;
        dsu.mx[i] = a;
    }

    for(int i = 0; i < n; ++i) {
        dsu.r[i] = i + 1;
        dsu.l[i] = i - 1;
    }

    auto check = [&](int a, int b) {
        if(dsu.mx[a] + 1 == dsu.mn[b] || dsu.mn[a] - 1 == dsu.mx[b]) return true;
        if(dsu.mx[b] + 1 == dsu.mn[a] || dsu.mn[b] - 1 == dsu.mx[a]) return true;
        return false;
    };

    queue<int> q;
    for(int i = 0; i < n; ++i) {
        q.push(i);
    }

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        cur = dsu.find(cur);
        
        if(dsu.l[cur] >= 0) {
            int nxt = dsu.find(dsu.l[cur]);
            if(check(cur, nxt)) {
                dsu.uni(cur, nxt);
                q.push(dsu.find(cur));
            }
        }

        cur = dsu.find(cur);
        if(dsu.r[cur] < n) {
            int nxt = dsu.find(dsu.r[cur]);
            if(check(cur, nxt)) {
                dsu.uni(cur, nxt);
                q.push(dsu.find(cur));
            }
        }
     }

    int rt = dsu.find(0);
    if(dsu.sz[rt] == n) cout << "YES";
    else cout << "NO";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
