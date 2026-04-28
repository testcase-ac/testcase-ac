#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int solve_pw2(int p, int n) {
  if (p % 2 == 0) return 0;
  else {
    if (n & 1) return 0;
    else {
      n /= 2;
      int t = 0, q = p + 1;
      while (q % 2 == 0) q /= 2, ++t;
      while (n % 2 == 0) n /= 2, ++t;
      return t;
    }
  }
}

int solve_pw3(int p, int n) {
  if (p % 3 == 0) return 0;
  else if (p % 3 == 1) {
    int t = 0;
    while (n % 3 == 0) n /= 3, ++t;
    return t;
  }
  else {
    if (n & 1) return 0;
    else {
      n /= 2;
      int t = 0, q = p + 1;
      while (q % 3 == 0) q /= 3, ++t;
      while (n % 3 == 0) n /= 3, ++t;
      return t;
    }
  }
}

void solve() {
  int p, n; cin >> p >> n;
  cout << solve_pw2(p, n) << ' ' << solve_pw3(p, n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
