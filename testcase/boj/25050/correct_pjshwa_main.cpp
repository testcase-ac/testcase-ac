#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXV = 2000, MAXE = 5000;
const ll INF = 1e18;
vector<tii> graph[MAXV + 1];
ll cdist[MAXV + 1];
pll from[MAXV + 1];
ll si[MAXE + 1];

void dijk(int s) {
  for (int i = 1; i <= MAXV; i++) {
    cdist[i] = INF;
    from[i] = {-1, -1};
  }
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [di, vi, ei] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        from[vi] = {ui, ei};
        pq.push({cdist[vi], vi});
      }
    }
  }
}

vector<pii> to[MAXV + 1];
bool vis[MAXV + 1];

int dfs(int v) {
  vis[v] = 1;

  int res = 0;
  for (auto& [d, e] : to[v]) {
    if (!vis[d]) {
      int cur = dfs(d);
      si[e] += cur;
      res += cur;
    }
  }

  return res + 1;
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({w, v, i});
  }

  for (int i = 1; i <= n; i++) {
    dijk(i);

    for (int j = 1; j <= n; j++) to[j].clear();
    memset(vis, 0, sizeof(vis));

    for (int j = 1; j <= n; j++) {
      if (from[j].first == -1) continue;
      to[from[j].first].push_back({j, from[j].second});
    }

    dfs(i);

    // for (int s = 1; s <= m; s++) {
    //   cout << "si[" << s << "] = " << si[s] << endl;
    // }
  }

  ll mval = *max_element(si + 1, si + m + 1);
  vector<int> ans;
  for (int i = 1; i <= m; i++) {
    if (si[i] == mval) ans.push_back(i);
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
