#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  for (int a = 1; a <= n; a++) {
    if (n % a) continue;
    int c = n / a;

    for (int p = 1; p <= n + 2; p++) {
      if ((n + 2) % p) continue;

      int q = (n + 2) / p;
      for (auto [b, d] : {pii(p, -q), pii(-p, q), pii(q, -p), pii(-q, p)}) {
        if (a * c == n && a * d + b * c == n + 1) {
          cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
          exit(0);
        }
      }
    }
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
