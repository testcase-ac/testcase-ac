#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;

void solve() {
  int n, T;
  cin >> n >> T;
  vector<tii> cities(n + 1);
  for (int i = 1; i <= n; i++) {
    int s, x, y;
    cin >> s >> x >> y;
    cities[i] = {s, x, y};
  }

  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;

    auto [us, ux, uy] = cities[u];
    auto [vs, vx, vy] = cities[v];

    int res = abs(ux - vx) + abs(uy - vy);
    int umin = INF, vmin = INF;
    for (int i = 1; i <= n; i++) {
      auto [si, xi, yi] = cities[i];
      if (!si) continue;

      umin = min(umin, abs(xi - ux) + abs(yi - uy));
      vmin = min(vmin, abs(xi - vx) + abs(yi - vy));
    }
    res = min(res, umin + vmin + T);

    cout << res << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
