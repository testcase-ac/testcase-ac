#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
const ll INF = 1e18;
pii statues[MAX + 1];
ll d[MAX + 1][MAX + 1];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= k; i++) cin >> statues[i].second >> statues[i].first;
  sort(statues + 1, statues + k + 1);

  for (int i = 1; i <= k; i++) for (int j = 0; j <= n; j++) d[i][j] = INF;

  // minimum cost to have i statues upto streetlight j
  for (int i = 1; i <= k; i++) for (int j = 1; j <= n; j++) {
    auto [w, p] = statues[i];
    d[i][j] = min(d[i][j - 1], d[i - 1][j - 1] + (ll)abs(j - p) * w);
  }

  cout << d[k][n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
