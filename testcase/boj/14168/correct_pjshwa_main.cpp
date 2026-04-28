#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1000, INF = 1e18;
ll d[MAX + 1][MAX + 1][2];
int Hx[MAX + 1], Hy[MAX + 1], Gx[MAX + 1], Gy[MAX + 1];
int H, G;

ll dist(ll x1, ll y1, ll x2, ll y2) {
  return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

ll r(int i, int j, int p) {
  if (d[i][j][p] != -1) return d[i][j][p];
  if (i == H && j == G) return d[i][j][p] = (p == 0 ? 0 : INF);

  ll ret = INF;
  if (i < H) {
    if (p) {
      ret = min(ret, r(i + 1, j, 0) + dist(Gx[j], Gy[j], Hx[i + 1], Hy[i + 1]));
    }
    else {
      ret = min(ret, r(i + 1, j, 0) + dist(Hx[i], Hy[i], Hx[i + 1], Hy[i + 1]));
    }
  }
  if (j < G) {
    if (p) {
      ret = min(ret, r(i, j + 1, 1) + dist(Gx[j], Gy[j], Gx[j + 1], Gy[j + 1]));
    }
    else {
      ret = min(ret, r(i, j + 1, 1) + dist(Hx[i], Hy[i], Gx[j + 1], Gy[j + 1]));
    }
  }
  return d[i][j][p] = ret;
}

void solve() {
  cin >> H >> G;
  for (int i = 1; i <= H; i++) cin >> Hx[i] >> Hy[i];
  for (int i = 1; i <= G; i++) cin >> Gx[i] >> Gy[i];

  memset(d, -1, sizeof(d));
  cout << r(1, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
