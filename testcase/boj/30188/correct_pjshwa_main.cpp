#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int S, N, U, P, C; cin >> S >> N >> U >> P >> C;

  if (S > 0 || N > 0 || U > 1) cout << "hanbyeol\n";
  else if (U == 1) {
    if (P & 1) cout << "geometry\n";
    else cout << "hanbyeol\n";
  }
  else if (P & 1) cout << "geometry\n";
  else cout << "number_theory\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
