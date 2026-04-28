#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1005;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int T[MAX + 5][MAX + 5], V[MAX + 5][MAX + 5];

void solve() {
  int N; cin >> N;

  int cur = 0;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;

    V[x][y] = 1;
    if (T[x][y] == 3) cur++;

    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) continue;

      if (T[nx][ny] == 3 && V[nx][ny]) cur--;
      T[nx][ny]++;
      if (T[nx][ny] == 3 && V[nx][ny]) cur++;
    }

    cout << cur << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
