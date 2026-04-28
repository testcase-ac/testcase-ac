#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int MAX = 1e5;
pii c[MAX];
bool vis[MAX];
int cnt, n;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void mark_all(pii a, pii b) {
  int dx = a.first - b.first, dy = a.second - b.second;
  if (dx == 0) {
    for (int i = 0; i < n; i++) {
      if (!vis[i] && c[i].first == a.first) vis[i] = true, cnt++;
    }
  }
  else if (dy == 0) {
    for (int i = 0; i < n; i++) {
      if (!vis[i] && c[i].second == a.second) vis[i] = true, cnt++;
    }
  }
  else {
    int g = __gcd(abs(dx), abs(dy));
    dx /= g, dy /= g;
    for (int i = 0; i < n; i++) {
      if (
        !vis[i] &&
        abs(c[i].first - a.first) % abs(dx) == 0 &&
        abs(c[i].second - a.second) % abs(dy) == 0 &&
        (c[i].first - a.first) / dx == (c[i].second - a.second) / dy
      ) vis[i] = true, cnt++;
    }
  }
}

int main() {
  fast_io();

  cin >> n;
  if (n <= 4) return cout << "success\n", 0;
  for (int i = 0; i < n; i++) cin >> c[i].first >> c[i].second;

  mt19937 rng(0x14004);
  auto randint = [&rng](int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
  };

  int it = 100;
  while (it--) {
    int ai = randint(0, n - 1);
    int bi = randint(0, n - 1);
    while (ai == bi) bi = randint(0, n - 1);

    cnt = 0;
    memset(vis, 0, sizeof(vis));
    mark_all(c[ai], c[bi]);

    int ci = -1, di = -1;
    for (int i = 0; i < n; i++) {
      if (vis[i]) continue;
      if (ci == -1) ci = i;
      else {
        di = i;
        break;
      }
    }
    mark_all(c[ci], c[di]);

    if (cnt == n) return cout << "success\n", 0;
  }

  cout << "failure\n";
}
