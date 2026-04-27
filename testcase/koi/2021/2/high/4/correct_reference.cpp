#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cassert>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using ti = tuple<int,int,int>;

const int LG = 20;
int n, m;
vector<vector<int>> G; // N
vector<int> dep, ord; // N
vector<array<int,LG>> par; // N * logN
vector<int> pcen; // N

vector<vector<int>> RB;// N, Responsible Balls
vector<ti> BZ; // all balls
vector<vector<int>> B; // N, balls centered at x

struct hmap : vector<ll> {
    ll get(int x) {
        if(x < 0 || x >= int(size())) return 0ll;
        return *(begin()+x);
    }
    void add(int x, ll v) {
        if(x < 0 || x >= int(size())) {
            assert(0);
        }
        *(begin() + x) += v;
    }
};
vector<hmap> subdp, pardp;

namespace Cent {
    vector<int> sz; // N
    vector<bool> del; // N
    vector<int> vis; // N
    int vlk;
    void init() {
        sz.resize(n + 1);
        del.resize(n + 1);
        vis.resize(n + 1);
        vlk = 0;
    }
    void dfs(int x) {
        vis[x] = vlk;
        sz[x] = 1;
        for(int u : G[x]) {
            if(del[u] || vis[u] == vlk) continue;
            dfs(u);
            sz[x] += sz[u];
        }
    }

    int cen(int x, int tot) {
        pii msz(0, -1);
        for(int u : G[x]) {
            if(del[u] || vis[u] != vlk || sz[u] > sz[x]) continue;
            msz = max(msz, pii(sz[u], u));
        }
        if(msz.first * 2 <= tot) return x;
        return cen(msz.second, tot);
    }

    int dnc(int x) {
        ++vlk;
        dfs(x);
        int c = cen(x, sz[x]);
        subdp[c].resize(sz[x] + 1);
        pardp[c].resize(sz[x] + 1);
        del[c] = true;
        for(int u : G[c]) {
            if(del[u]) continue;
            int r = dnc(u);
            pcen[r] = c;
        }
        return c;
    }
}

vector<vector<int>> ballsToRetrieve; // N
vector<ll> dp; // N

int dfs_clk;
void dfs(int x) {
    ++dep[x];
    ord.push_back(x);
    for(int i = 1; i < LG; i++) par[x][i] = par[par[x][i-1]][i-1];
    for(int u : G[x]) {
        if(dep[u]) continue;
        dep[u] = dep[x]; par[u][0] = x;
        dfs(u);
    }
    for(auto j : B[x]) {
        ballsToRetrieve[max(1, dep[x] - get<1>(BZ[j]))].push_back(j);
    }
    RB[x] = ballsToRetrieve[ dep[x] ]; ballsToRetrieve[ dep[x] ].clear();
}

int lca(int i, int j) {
    if(dep[i] < dep[j]) swap(i, j);
    for(int a = dep[i] - dep[j], k = 0; a; a >>= 1, k++) {
        if(a & 1) i = par[i][k];
    }
    for(int l = 19; l >= 0; l--) {
        if(par[i][l] != par[j][l]) {
            i = par[i][l], j = par[j][l];
        }
    }
    return i == j ? i : par[i][0];
}

int dist(int i, int j) {
    int l = lca(i, j);
    return dep[i] + dep[j] - 2*dep[l];
}

ll collect_dp(int x, int d) {
    ll ans = 0;
    for(int v = x; v; v = pcen[v]) {
        int r = dist(v, x);
        ans += subdp[v].get(d - r);
        if(pcen[v]) {
            int s = dist(pcen[v], x);
            ans -= pardp[v].get(d - s);
        }
    }
    return ans;
}

void update_dp(int x, ll val) {
    for(int v = x; v; v = pcen[v]) {
        int r = dist(v, x);
        subdp[v].add(r, val);
        if(pcen[v]) {
            int s = dist(pcen[v], x);
            pardp[v].add(s, val);
        }
    }
}

void dfs_dp(int x) {
    for(int u : G[x]) {
        if(dep[u] < dep[x]) continue;
        dfs_dp(u);
        dp[x] += dp[u];
    }
    for(auto j : RB[x]) {
        auto [c, d, g] = BZ[j];
        ll local_dp = collect_dp(c, d+1);
        dp[x] = max(dp[x], g + local_dp);
    }
    update_dp(x, dp[x]);
}

void init() {
    G.resize(n + 1);
    dep.resize(n + 1);
    par.resize(n + 1);
    pcen.resize(n + 1);
    RB.resize(n + 1);
    B.resize(n + 1);
    ballsToRetrieve.resize(n + 1);
    subdp.resize(n + 1);
    pardp.resize(n + 1);
    dp.resize(n + 1);
    Cent::init();
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    cin >> n >> m;
    init();

    for(int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    Cent::dnc(1);
    for(int i = 0, c,d,g; i < m; i++) {
        cin >> c >> d >> g;
        BZ.emplace_back(c, d, g);
        B[c].push_back(i);
    }

    dfs(1);
    dfs_dp(1);
    cout << dp[1] << '\n';
}