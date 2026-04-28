#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1005;
ll A[MAX + 1][MAX + 1], P[MAX + 1][MAX + 1];

void preprocess() {
  for (int i = 1; i <= MAX; i++) {
    P[i][0] += P[i - 1][0];
    P[0][i] += P[0][i - 1];
  }
  for (int i = 1; i <= MAX; i++) for (int j = 1; j <= MAX; j++) {
    P[i][j] += P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
  }
  for (int i = 0; i <= MAX; i++) for (int j = 0; j <= MAX; j++) {
    P[i][j] += A[i][j];
    if (i) P[i][j] += P[i - 1][j];
    if (j) P[i][j] += P[i][j - 1];
    if (i && j) P[i][j] -= P[i - 1][j - 1];
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> A[i][j];

  bool f = true;
  while (m--) {
    int op, x1, y1, x2, y2;
    cin >> op >> x1 >> y1 >> x2 >> y2;
    if (op == 1) {
      int k;
      cin >> k;
      P[x1][y1] += k;
      P[x1][y2 + 1] -= k;
      P[x2 + 1][y1] -= k;
      P[x2 + 1][y2 + 1] += k;
    }
    if (op == 2) {
      if (f) {
        preprocess();
        f = false;
      }

      ll ret = P[x2][y2];
      if (x1) ret -= P[x1 - 1][y2];
      if (y1) ret -= P[x2][y1 - 1];
      if (x1 && y1) ret += P[x1 - 1][y1 - 1];
      cout << ret << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
