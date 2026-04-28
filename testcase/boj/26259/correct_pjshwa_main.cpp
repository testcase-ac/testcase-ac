#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
int A[MAX + 1][MAX + 1], d[MAX + 1][MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      cin >> A[i][j];
    }
  }
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  if (x1 > x2) swap(x1, x2);
  if (y1 > y2) swap(y1, y2);

  for (int i = 0; i <= N; ++i) {
    fill(d[i], d[i] + M + 1, -INF);
  }
  d[1][1] = A[1][1];

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      if (x1 == x2 && i == x1 + 1 && j > y1 && j <= y2) {}
      else if (d[i - 1][j] != -INF) d[i][j] = max(d[i][j], d[i - 1][j] + A[i][j]);

      if (y1 == y2 && j == y1 + 1 && i > x1 && i <= x2) {}
      else if (d[i][j - 1] != -INF) d[i][j] = max(d[i][j], d[i][j - 1] + A[i][j]);
    }
  }

  if (d[N][M] == -INF) cout << "Entity\n";
  else cout << d[N][M] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
