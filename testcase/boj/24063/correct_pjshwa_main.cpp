#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
const ll INF = 1e18;
ll cost[MAX + 1];
ll n, e, m;
vector<pii> graph[MAX + 1];
vector<tii> info;
bool vis[MAX + 1];

ll ccost, cstart;
void dfs(int v) {
  vis[v] = 1;
  if (cost[v] < ccost) {
    ccost = cost[v];
    cstart = v;
  }
  for (auto [d, w] : graph[v]) {
    if (!vis[d]) dfs(d);
  }
}

ll coef[MAX + 1];
bool neg[MAX + 1];
bool has_cycle;
set<ll> candidates;

void dfs_find_candidate(int v, int par, ll cf, bool n) {
  vis[v] = 1;
  coef[v] = cf;
  neg[v] = n;

  for (auto [d, w] : graph[v]) {
    if (vis[d]) {
      if (d == par) continue;

      if (has_cycle == 0) {
        ll av = cf + coef[d];
        if (neg[v] == 1 && neg[d] == 1) {
          has_cycle = 1;
          ll v1 = av + m - w, v2 = av - w;
          for (ll val : {v1, v2}) {
            if (val % 2 == 0) {
              ll ival = val / 2;
              while (ival < 0) ival += m;
              candidates.insert(ival % m);
            }
          }
        }
        else if (neg[v] == 0 && neg[d] == 0) {
          has_cycle = 1;
          ll v1 = w - av + m, v2 = w - av;
          for (ll val : {v1, v2}) {
            if (val % 2 == 0) {
              ll ival = val / 2;
              while (ival < 0) ival += m;
              candidates.insert(ival % m);
            }
          }
        }
        else if (av % m != w % m) {
          cout << "-1\n";
          exit(0);
        }
        else continue;

        // cout << "v: " << v << ", av: " << av << ", d: " << d << ", w: " << w << endl;
        // for (ll e : candidates) cout << e << ' ';
        // cout << '\n';
      }
      else {
        set<ll> ncandidates;
        ll av = cf + coef[d];
        if (neg[v] == 1 && neg[d] == 1) {
          ll v1 = av + m - w, v2 = av - w;
          for (ll val : {v1, v2}) {
            if (val % 2 == 0) {
              ll ival = val / 2;
              while (ival < 0) ival += m;
              ncandidates.insert(ival % m);
            }
          }
        }
        else if (neg[v] == 0 && neg[d] == 0) {
          ll v1 = w - av + m, v2 = w - av;
          for (ll val : {v1, v2}) {
            if (val % 2 == 0) {
              ll ival = val / 2;
              while (ival < 0) ival += m;
              ncandidates.insert(ival % m);
            }
          }
        }
        else if (av % m != w % m) {
          cout << "-1\n";
          exit(0);
        }
        else continue;

        // cout << "v: " << v << ", av: " << av << ", d: " << d << ", w: " << w << endl;
        // for (int e : candidates) cout << e << ' ';
        // cout << '\n';
        // for (int e : ncandidates) cout << e << ' ';
        // cout << '\n';

        set<ll> remove;
        for (auto c : candidates) {
          if (!ncandidates.count(c)) remove.insert(c);
        }
        for (auto c : remove) candidates.erase(c);
      }
    }
    else dfs_find_candidate(d, v, (w + m - cf) % m, !n);
  }
}

bool vism[MAX + 1];
ll pa[MAX + 1];

void dfs_mark(int v, ll val) {
  vism[v] = 1;
  while (val <= 0) val += m;
  pa[v] = val;
  for (auto [d, w] : graph[v]) {
    if (!vism[d]) dfs_mark(d, w - val);
  }
}

void solve() {
  cin >> n >> e >> m;
  for (int i = 1; i <= n; i++) cin >> cost[i];

  for (int i = 0; i < e; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
    info.push_back({a, b, c});
  }

  ll acost = 0;
  vector<int> spositions;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      ccost = INF;
      dfs(i);
      acost += ccost;
      spositions.push_back(cstart);
    }
  }

  memset(vis, 0, sizeof vis);
  for (int e : spositions) {
    candidates.clear();
    has_cycle = 0;
    dfs_find_candidate(e, -1, 0, 0);

    if (!has_cycle) dfs_mark(e, 1);
    else if (candidates.size() == 0) return cout << "-1\n", void();
    else {
      dfs_mark(e, *candidates.begin());
      if (candidates.size() == 1) acost -= cost[e];
    }
  }

  for (auto [a, b, c] : info) {
    if ((pa[a] + pa[b]) % m != c) return cout << "-1\n", void();
  }

  cout << acost << '\n';
  for (int i = 1; i <= n; i++) cout << pa[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
