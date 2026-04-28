#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Usage {
  int a, b, c, d;

  bool operator<(const Usage& rhs) const {
    return a + b + c + d < rhs.a + rhs.b + rhs.c + rhs.d;
  }
};

void solve() {
  int X, A, B, C, D;
  cin >> X >> A >> B >> C >> D;

  int Ar = 0;
  if (X % 5) {
    if (A < X % 5) return cout << "0 0 0 0\n", void();
    Ar += X % 5;
    A -= X % 5;
    X -= X % 5;
  }

  Usage u = {0, 0, 0, 0};
  for (int Duse = 0; Duse <= D; Duse++) {
    if (Duse * 25 > X) break;

    for (int Cuse = 0; Cuse <= C; Cuse++) {
      if (Duse * 25 + Cuse * 10 > X) break;

      for (int Buse = 0; Buse <= B; Buse++) {
        if (Duse * 25 + Cuse * 10 + Buse * 5 > X) break;

        int Ause = (X - Duse * 25 - Cuse * 10 - Buse * 5);
        if (Ause > A) continue;

        Usage cand = {Ause + Ar, Buse, Cuse, Duse};
        u = max(u, cand);
      }
    }
  }

  cout << u.a << ' ' << u.b << ' ' << u.c << ' ' << u.d << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
