#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int X, Y; cin >> X >> Y;
  int cx = 0, cy = 0;

  if (X == 0 || Y == 0) {
    vector<pii> D = {{1, 0}, {0, 1}, {0, 1}, {-1, 0}, {-1, 0}, {0, -1}, {1, 0}};
    cout << D.size() << '\n';
    for (auto [dx, dy] : D) {
      cx += dx * max(X, Y);
      cy += dy * max(X, Y);
      cout << cx << ' ' << cy << '\n';
    }
  }
  else if (X == Y) {
    vector<pii> D = {{1, 1}, {1, -1}, {1, -1}, {-1, -1}, {-1, -1}, {-1, 1}, {1, 1}};
    cout << D.size() << '\n';
    for (auto [dx, dy] : D) {
      cx += dx * X;
      cy += dy * X;
      cout << cx << ' ' << cy << '\n';
    }
  }
  else {
    vector<pii> D = {
      {X, Y}, {X, -Y}, {X, -Y}, {-X, -Y}, {-X, -Y}, {-X, Y}, {Y, X}, {X, Y},
      {Y, -X}, {-Y, -X}, {-Y, -X}, {-Y, X}, {-Y, X}, {Y, X}, {Y, -X},
    };
    cout << D.size() << '\n';
    for (auto [dx, dy] : D) {
      cx += dx;
      cy += dy;
      cout << cx << ' ' << cy << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
