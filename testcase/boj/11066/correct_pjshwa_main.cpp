#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
int cost[MAX + 1], d[MAX + 1][MAX + 1];
int n;

int min_cost(int l, int r) {
  if (l == r) return 0;
  if (d[l][r] != -1) return d[l][r];

  int ans = INF;
  for (int i = l; i < r; i++) {
    ans = min(ans, min_cost(l, i) + min_cost(i + 1, r));
  }
  return d[l][r] = ans + cost[r] - cost[l - 1];
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> cost[i], cost[i] += cost[i - 1];
  memset(d, -1, sizeof(d));
  cout << min_cost(1, n) << '\n';
}

int main() {
  fast_io();
  
  int t;
  cin >> t;
  while (t--) solve();
}
