#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
int A[MAXN + 1], B[MAXN + 1], N;

void check_possible(int l1, int r1, int l2, int r2) {
  {
    iota(A + 1, A + N + 1, 1);
    reverse(A + l1, A + r1 + 1);
    reverse(A + l2, A + r2 + 1);

    bool ok = true;
    for (int i = 1; i <= N; ++i) ok &= (A[i] == B[i]);
    if (ok) {
      cout << l2 << " " << r2 << "\n";
      cout << l1 << " " << r1 << "\n";
      exit(0);
    }
  }
  {
    iota(A + 1, A + N + 1, 1);
    reverse(A + l2, A + r2 + 1);
    reverse(A + l1, A + r1 + 1);

    bool ok = true;
    for (int i = 1; i <= N; ++i) ok &= (A[i] == B[i]);
    if (ok) {
      cout << l1 << " " << r1 << "\n";
      cout << l2 << " " << r2 << "\n";
      exit(0);
    }
  }
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; ++i) cin >> B[i];
  B[N + 1] = N + 1;

  int x = 1, y = 1;
  for (int i = 1; i <= N; ++i) {
    if (B[i] != i) {
      x = i;
      break;
    }
  }
  for (int i = N; i >= 1; --i) {
    if (B[i] != i) {
      y = i;
      break;
    }
  }

  // ans must be one of these
  // [x, y], [z1, z2] where x <= z1, z2 <= y
  int z1 = 1, z2 = 1;
  for (int i = x; i <= y; ++i) {
    int tar = y - (i - x);
    if (B[i] != tar) {
      z1 = i;
      break;
    }
  }
  for (int i = y; i >= x; --i) {
    int tar = y - (i - x);
    if (B[i] != tar) {
      z2 = i;
      break;
    }
  }

  check_possible(z1, z2, x, y);

  // [x, z1], [z2, y] where x <= z2, z1 <= y
  int xp, yp;
  for (int i = x; i <= y; ++i) {
    if (B[i] == x) xp = i;
    if (B[i] == y) yp = i;
  }

  // [x, xp], [yp, y], xp <= yp
  for (auto [l1, r1, l2, r2] : vector<tuple<int, int, int, int>>{
    {x, xp, yp, y},
    {x, yp, yp, y},
    {yp, y, x, yp},
  }) check_possible(l2, r2, l1, r1);

  // xp > yp
  // if [xp, y] is increasing by 1
  {
    bool ok = true;
    for (int i = xp + 1; i <= y; ++i) {
      ok &= (B[i] == B[i - 1] + 1);
    }
    if (ok) {
      int len = y - xp + 1;
      check_possible(B[x] - len + 1, y, x, B[x]);
    }
  }

  // if [x, yp] is increasing by 1
  {
    bool ok = true;
    for (int i = x + 1; i <= yp; ++i) {
      ok &= (B[i] == B[i - 1] + 1);
    }
    if (ok) {
      int len = yp - x + 1;
      check_possible(B[y], y, x, B[y] + len - 1);
    }
  }

  assert(false);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
