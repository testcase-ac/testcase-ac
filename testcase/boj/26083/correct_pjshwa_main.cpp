#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void solve() {
  int Y, M, D, Q;
  cin >> Y >> M >> D >> Q;
  while (Q--) {
    int A, B, C;
    cin >> A >> B >> C;

    bool safe = true, valid = false;
    for (auto [y, m, d] : {tii(A, B, C), tii(C, B, A), tii(C, A, B)}) {
      if (m < 1 || m > 12) continue;
      if (d < 1) continue;

      if (y % 4 == 0 && m == 2) {
        if (d > 29) continue;
      }
      else if (d > days[m]) continue;

      valid = true;
      if (y < Y || (y == Y && m < M) || (y == Y && m == M && d < D)) {
        safe = false;
      }
    }

    if (valid) {
      if (safe) cout << "safe\n";
      else cout << "unsafe\n";
    }
    else cout << "invalid\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
