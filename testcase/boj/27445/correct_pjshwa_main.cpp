#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
int D[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i < N; i++) cin >> D[i][1];
  for (int j = 1; j <= M; j++) cin >> D[N][j];

  auto dist = [&](int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
  };
  for (int r = 1; r <= N; r++) for (int c = 1; c <= M; c++) {
    bool ok = true;
    for (int i = 1; i < N; i++) ok &= dist(r, c, i, 1) == D[i][1];
    for (int j = 1; j <= M; j++) ok &= dist(r, c, N, j) == D[N][j];

    if (ok) {
      cout << r << " " << c << "\n";
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
