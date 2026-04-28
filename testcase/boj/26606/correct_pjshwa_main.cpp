#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int d[MAX + 1][MAX + 1][MAX + 1];
int L[MAX + 1], R[MAX + 1], N;

bool placeable_l(int p, int c) {
  return c > p || abs(p - c) == 10;
}

bool placeable_r(int p, int c) {
  return c < p || abs(p - c) == 10;
}

int rec(int i, int l, int r) {
  if (d[i][l][r] != -1) return d[i][l][r];
  if (i == N) return d[i][l][r] = 1;

  int cl = L[i], cr = R[i], ret = 0;

  if (placeable_l(l, cl) && placeable_r(cl, cr)) ret |= rec(i + 1, cr, r);
  if (placeable_l(l, cl) && placeable_r(r, cr)) ret |= rec(i + 1, cl, cr);
  if (placeable_l(l, cr) && placeable_r(cr, cl)) ret |= rec(i + 1, cl, r);
  if (placeable_l(l, cr) && placeable_r(r, cl)) ret |= rec(i + 1, cr, cl);

  if (placeable_l(r, cl) && placeable_r(cl, cr)) ret |= rec(i + 1, l, cr);
  if (placeable_l(r, cl) && placeable_r(l, cr)) ret |= rec(i + 1, cr, cl);
  if (placeable_l(r, cr) && placeable_r(cr, cl)) ret |= rec(i + 1, l, cl);
  if (placeable_l(r, cr) && placeable_r(l, cl)) ret |= rec(i + 1, cl, cr);

  return d[i][l][r] = ret;
}

void solve() {
  cin >> N;
  N /= 2;
  for (int i = 0; i < N; i++) cin >> L[i] >> R[i];

  memset(d, -1, sizeof(d));
  if (rec(0, 0, 0)) cout << "WIN\n";
  else cout << "LOSE\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
