#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int A[5];
ll d[11][11][11][11][11][6][6];

ll r(int c1, int c2, int c3, int c4, int c5, int l1, int l2) {
  if (c1 + c2 + c3 + c4 + c5 == 0) return 1;
  if (d[c1][c2][c3][c4][c5][l1][l2] != -1) return d[c1][c2][c3][c4][c5][l1][l2];

  ll res = 0;
  if (c1 && l1 != 1 && l2 != 1) res += r(c1 - 1, c2, c3, c4, c5, 1, l1);
  if (c2 && l1 != 2 && l2 != 2) res += r(c1, c2 - 1, c3, c4, c5, 2, l1);
  if (c3 && l1 != 3 && l2 != 3) res += r(c1, c2, c3 - 1, c4, c5, 3, l1);
  if (c4 && l1 != 4 && l2 != 4) res += r(c1, c2, c3, c4 - 1, c5, 4, l1);
  if (c5 && l1 != 5 && l2 != 5) res += r(c1, c2, c3, c4, c5 - 1, 5, l1);

  return d[c1][c2][c3][c4][c5][l1][l2] = res;
}

void solve() {
  int K;
  cin >> K;
  for (int i = 0; i < K; i++) cin >> A[i];

  memset(d, -1, sizeof(d));
  cout << r(A[0], A[1], A[2], A[3], A[4], 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
