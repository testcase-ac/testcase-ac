#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<vector<int>> g(MAX + 1);
int c[MAX + 1], gp[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int q;
    cin >> q;
    while (q--) {
      int x;
      cin >> x;
      g[i].push_back(x);
    }
  }
  for (int i = 1; i <= n; i++) cin >> c[i];

  vector<int> sim(n + 1);
  for (int i = 1; i <= n; i++) sim[i] = c[i];

  for (int i = m; i >= 1; i--) {
    int infc = 1;
    for (int p : g[i]) infc &= sim[p];
    if (!infc) for (int p : g[i]) sim[p] = 0;
  }

  vector<int> ans = sim;
  for (int i = 1; i <= m; i++) {
    int infc = 0;
    for (int p : g[i]) infc |= sim[p];
    if (infc) for (int p : g[i]) sim[p] = 1;
  }

  for (int i = 1; i <= n; i++) {
    if (sim[i] != c[i]) return cout << "NO\n", void();
  }

  cout << "YES\n";
  for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
