#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll f[MAX + 1], indegree[MAX + 1];
vector<int> graph[MAX + 1];
pll u[MAX + 1];
int tc;

void solve() {
  cout << "Case #" << ++tc << ": ";

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> f[i];

  for (int i = 1; i <= n; i++) graph[i].clear();
  memset(indegree, 0, sizeof(indegree));

  vector<int> terminals;
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> p;
    if (p == 0) terminals.push_back(i);
    else {
      graph[i].push_back(p);
      indegree[p]++;
    }
    u[i] = {-1, -1};
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) {
      u[i] = {f[i], f[i]};
      q.push(i);
    }
  }

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    ll diff = max(0LL, f[v] - u[v].first);
    u[v] = {u[v].first + diff, u[v].second + diff};

    for (int d : graph[v]) {
      if (u[d].first == -1) u[d] = u[v];
      else {
        u[d].first = min(u[d].first, u[v].first);
        u[d].second += u[v].second;
      }

      if (!--indegree[d]) q.push(d);
    }
  }

  ll ans = 0;
  for (int e : terminals) ans += u[e].second;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
