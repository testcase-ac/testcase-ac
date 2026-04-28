#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[6] = {-1, -1, 0, 1, 1, 0}, dy[6] = {1, 0, -1, -1, 0, 1};

void solve() {
  int X, Y; cin >> X >> Y;
  if (X == 0 && Y == 0) return void(cout << "1\n");

  ll D = max({abs(X + Y), abs(X), abs(Y)}), U = 0;
  for (int i = 1; i <= D - 1; i++) U += 6 * i;

  int x = D, y = 0;
  for (int k = 0; k < 6; k++) {
    for (int l = 0; l < D; l++) {
      x += dx[k], y += dy[k];
      U++;
      if (x == X && y == Y) {
        cout << U + 1 << '\n';
        return;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
