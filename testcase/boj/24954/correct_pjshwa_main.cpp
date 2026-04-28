#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10;
int c[MAX + 1];
vector<pii> dcs[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> c[i];
  for (int i = 0; i < n; i++) {
    int e;
    cin >> e;
    while (e--) {
      int x, v;
      cin >> x >> v;
      dcs[i].push_back({x - 1, v});
    }
  }

  int p[n];
  for (int i = 0; i < n; i++) p[i] = i;

  int ans = 1e9;
  do {
    int cur[n];
    for (int i = 0; i < n; i++) cur[i] = c[i];

    int cval = 0;
    for (int i = 0; i < n; i++) {
      int v = p[i];
      cval += cur[v];
      for (auto& [x, d] : dcs[v]) cur[x] = max(1, cur[x] - d);
    }
    ans = min(ans, cval);

  } while (next_permutation(p, p + n));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
