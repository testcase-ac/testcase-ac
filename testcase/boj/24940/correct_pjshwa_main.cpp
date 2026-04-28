#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const ll INF = 1e18;
ll cost[MAX + 1], d[MAX + 1][MAX + 1];
int n;

ll min_cost(int l, int r) {
  if (l == r) return 0;
  if (d[l][r] != -1) return d[l][r];

  ll ans = INF;
  for (int i = l; i < r; i++) {
    ll get = min(0LL, (cost[r] - cost[i]) * (cost[i] - cost[l - 1]));
    ans = min(ans, min_cost(l, i) + min_cost(i + 1, r) + get);
  }
  return d[l][r] = ans;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> cost[i], cost[i] += cost[i - 1];
  memset(d, -1, sizeof(d));
  cout << min_cost(1, n) << '\n';
}

int main() {
  fast_io();
  
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
