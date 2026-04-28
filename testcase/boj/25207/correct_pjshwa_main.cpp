#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e6;
int a[MAX + 1];
vector<int> graph[MAX + 1];
pii se[MAX + 1], sv[MAX + 1];
int plen[MAX + 1], vs[MAX + 1], ve[MAX + 1];
int on;

void manacher() {
  int r = -1, p = -1;
  for (int i = 0; i < on; i++) {
    if (i <= r) plen[i] = min((2 * p - i >= 0) ? plen[2 * p - i] : 0, r - i);
    else plen[i] = 0;

    while (
      i - plen[i] - 1 >= 0 && i + plen[i] + 1 < on &&
      sv[i - plen[i] - 1] == sv[i + plen[i] + 1]
    ) plen[i] += 1;

    if (i + plen[i] > r) {
      r = i + plen[i];
      p = i;
    }
  }
}

int idx = 0;
void insert(int v, int d) {
  se[idx++] = {a[v], d};
}

void dfs(int v, int d) {
  insert(v, d);
  vs[v] = idx - 1;
  for (int u : graph[v]) {
    dfs(u, d + 1);
    insert(v, d);
  }
  ve[v] = idx - 1;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) sort(graph[i].begin(), graph[i].end());
  dfs(1, 1);

  on = (idx << 1) - 1;
  for (int i = 0; i < on; i++) {
    if (i % 2) sv[i] = {-1, -1};
    else sv[i] = se[i / 2];
  }

  manacher();

  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    int a = vs[i], b = ve[i];
    a <<= 1; b <<= 1;
    if (b - (a + b) / 2 <= plen[(a + b) / 2]) ans.push_back(i);
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
