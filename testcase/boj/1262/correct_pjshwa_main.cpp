#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, R1, C1, R2, C2; cin >> N >> R1 >> C1 >> R2 >> C2;

  int Z = 2 * N - 1, ci = N - 1, cj = N - 1;
  for (int i = R1; i <= R2; i++) {
    for (int j = C1; j <= C2; j++) {
      int pi = i % Z, pj = j % Z;

      int dis = abs(ci - pi) + abs(cj - pj);
      if (dis >= N) cout << '.';
      else cout << (char)('a' + (dis % 26));
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
