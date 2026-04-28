#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300;
ll d[MAX + 1][MAX + 1], A[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    A[x][y] = 1;
  }

  for (int i = 0; i <= MAX; i++) for (int j = 0; j <= MAX; j++) {
    int val = 0;
    if (A[i][j]) val = max(val, M - i - j);

    if (i) d[i][j] = max(d[i][j], d[i - 1][j] + val);
    if (j) d[i][j] = max(d[i][j], d[i][j - 1] + val);
  }
  cout << d[MAX][MAX] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
