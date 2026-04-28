#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
const ll INF = 1e18;
ll d[MAX + 1];

void solve() {
  int N, P, J;
  cin >> N >> P >> J;

  map<int, int> yc;
  vector<pii> pos(N + 1);
  for (int i = 1; i <= N; i++) {
    int x, y;
    cin >> x >> y;
    if (yc[y] > 2) return cout << "-1\n", void();

    yc[y]++;
    pos[i] = {y, x};
  }
  sort(pos.begin() + 1, pos.end());
  pos[0] = {0, 0};

  fill(d, d + MAX + 1, INF);
  d[0] = 0;
  for (int i = 1; i <= N; i++) {
    auto [y, x] = pos[i];

    if (i >= 1 && pos[i - 1].first == y) {
      if (i >= 2 && pos[i - 2].first == y - 1) {
        if (i >= 3 && pos[i - 3].first == y - 1) {
        }
        else {

        }
      }
      else {
        auto [ly, lx] = pos[i - 1];
        if (abs(lx - x) == 1) {

        }
      }
    }

    auto [ly, lx] = pos[i - 1];
    if (abs(ly - y) >= abs(lx - x)) {
      d[i] = min(d[i], d[i - 1] + abs(lx - x));
    }
  }

  if (d[N] == INF) cout << "-1\n";
  else cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
