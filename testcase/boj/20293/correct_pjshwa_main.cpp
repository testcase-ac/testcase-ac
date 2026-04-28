#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct pt {
  int x, y, f, d;
};

const int MAX = 1000, INF = 1e9 + 7;
pt u[MAX + 1];

int dist(pt a, pt b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

void solve() {
  int n, m, r;
  cin >> n >> m >> r;

  u[0] = {1, 1, 0, 0};
  for (int i = 1; i <= r; i++) cin >> u[i].x >> u[i].y >> u[i].f;
  for (int i = 0; i <= r; i++) {
    u[i].d = max(0, dist(u[i], {n, m, 0, 0}) - u[i].f);
  }
  sort(u, u + r + 1, [](pt a, pt b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });

  for (int i = r; i >= 0; i--) {
    for (int j = i - 1; j >= 0; j--) {
      if (u[i].y >= u[j].y) {
        u[j].d = min(u[j].d, max(0, u[i].d + dist(u[j], u[i]) - u[j].f));
      }
    }
  }

  cout << u[0].d << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
