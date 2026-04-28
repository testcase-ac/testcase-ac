#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
string s;
vector<int> graph[MAX + 1], rgraph[MAX + 1];
int indegree[MAX + 1];

void solve() {
  int n, m; 
  cin >> n >> m >> s;
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--; v--;

    if ((s[u] == 'K' && s[v] == 'D') || (s[u] == 'D' && s[v] == 'H') || (s[u] == 'H' && s[v] == 'K')) {
      rgraph[v].push_back(u);
      indegree[u]++;
    }
    if ((s[v] == 'K' && s[u] == 'D') || (s[v] == 'D' && s[u] == 'H') || (s[v] == 'H' && s[u] == 'K')) {
      rgraph[u].push_back(v);
      indegree[v]++;
    }
  }

  queue<pii> q;
  for (int i = 0; i < n; i++) {
    if (!indegree[i]) q.push({i, s[i] == 'H'});
  }

  int ans = 0, fc = 0;
  while (!q.empty()) {
    auto [v, c] = q.front();
    fc++;
    q.pop();

    if (c % 3 == 0) ans = max(ans, c);

    for (int u : rgraph[v]) {
      if (!--indegree[u]) {
        if (c == 0) q.push({u, s[u] == 'H'});
        else q.push({u, c + 1});
      }
    }
  }

  if (fc < n || ans == 0) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
