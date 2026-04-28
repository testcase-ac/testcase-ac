#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 200, INF = 0x3f3f3f3f;
int d[MAX + 1][MAX + 1][MAX + 1];

int r(int w, int l, int h) {
  if (w > l) swap(w, l);
  if (l > h) swap(l, h);
  if (w > l) swap(w, l);

  if (d[w][l][h] != -1) return d[w][l][h];
  if (w == l && l == h) return d[w][l][h] = 0;

  int ret = INF;
  for (int nw = 1; nw <= w / 2; nw++) {
    ret = min(ret, r(nw, l, h) + r(w - nw, l, h) + 1);
  }
  for (int nl = 1; nl <= l / 2; nl++) {
    ret = min(ret, r(w, nl, h) + r(w, l - nl, h) + 1);
  }
  for (int nh = 1; nh <= h / 2; nh++) {
    ret = min(ret, r(w, l, nh) + r(w, l, h - nh) + 1);
  }
  return d[w][l][h] = ret;
}

void solve() {
  int W, L, H;
  cin >> W >> L >> H;

  cout << r(W, L, H) + 1 << '\n';
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));

  int t = 1;
  cin >> t;
  while (t--) solve();
}
