#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int MAX = 500;
const ll INF = 2e6 + 1;
int v, x;

class Pipe {
public:
  ll l, c;

  Pipe() {};
  Pipe(ll l, ll c) : l(l), c(c) {}
  Pipe operator + (const Pipe &rhs) {
    return Pipe(l + rhs.l, min(c, rhs.c));
  }
  bool operator < (const Pipe &rhs) {
    return c * rhs.c * (l - rhs.l) < (c - rhs.c) * x;
  }
  bool operator <= (const Pipe &rhs) {
    return *this < rhs || (l == rhs.l && c == rhs.c);
  }
};

bool vis[MAX + 1];
Pipe cdist[MAX + 1];
Pipe graph[MAX + 1][MAX + 1];

void dijk(int s) {
  cdist[s] = {0, INF};

  for (int it = 1; it <= v - 1; it++) {
    Pipe md = {INF, 1};
    int mi = -1;
    for (int vi = 1; vi <= v; vi++) {
      if (!vis[vi] && cdist[vi] <= md) {
        md = cdist[vi];
        mi = vi;
      }
    }

    vis[mi] = true;
    for (int vi = 1; vi <= v; vi++) {
      if (!vis[vi] && cdist[mi] + graph[mi][vi] < cdist[vi]) {
        cdist[vi] = cdist[mi] + graph[mi][vi];
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int e;
  cin >> v >> e >> x;

  for (int i = 1; i <= v; i++) {
    cdist[i] = {INF, 1};
    for (int j = 1; j <= v; j++) graph[i][j] = {0, 0};
  }

  while (e--) {
    int x, y, l, c;
    cin >> x >> y >> l >> c;
    graph[x][y] = {l, c};
    graph[y][x] = {l, c};
  }

  dijk(1);

  auto [ll, lc] = cdist[v];
  cout << ll + x / lc << '\n';
}
