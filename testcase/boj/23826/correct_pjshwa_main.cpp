#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1001;
int e[MAX], w[MAX];
pii pts[MAX];

int manhattan_dist(pii& a, pii& b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i <= n; i++) {
    cin >> pts[i].first >> pts[i].second >> e[i];
  }

  for (int i = 1; i <= n; i++) {
    w[i] += max(0, e[0] - manhattan_dist(pts[0], pts[i]));
  }

  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    w[i] -= max(0, e[j] - manhattan_dist(pts[j], pts[i]));
  }

  int ans = -1;
  for (int i = 1; i <= n; i++) ans = max(ans, w[i]);

  if (ans <= 0) cout << "IMPOSSIBLE\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
