#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
int p[MAX + 1], u[MAX + 1], v[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) p[i] = i;
  for (int i = 1; i <= m; i++) cin >> u[i] >> v[i];
  for (int i = m; i >= 1; i--) p[u[i]] = p[v[i]];
  for (int i = 1; i <= n; i++) cout << p[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
