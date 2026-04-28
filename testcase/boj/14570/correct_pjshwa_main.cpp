#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
pii graph[MAX + 1];

void dfs(int v, ll k) {
  auto [l, r] = graph[v];
  if (l == -1 && r == -1) return cout << v << '\n', void();
  if (l == -1) dfs(r, k);
  else if (r == -1) dfs(l, k);
  else {
    if (k & 1) dfs(l, (k + 1) / 2);
    else dfs(r, (k + 1) / 2);
  }
}

void solve() {
  int n;
  ll k;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int l, r;
    cin >> l >> r;
    graph[i] = {l, r};
  }
  cin >> k;
  dfs(1, k);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
