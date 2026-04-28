#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;

  ll Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    Sx += x; Sy += y;
    Sxx += x * x; Sxy += x * y;
  }

  if (Sx * Sx == n * Sxx) cout << "EZPZ\n";
  else {
    ld a2_nom = n * Sxy - Sx * Sy;
    ld a2_den = n * Sxx - Sx * Sx;
    ld a2 = a2_nom / a2_den;

    ld b2_nom = Sy - a2 * Sx;
    ld b2_den = n;
    ld b2 = b2_nom / b2_den;

    cout << fixed << setprecision(9) << a2 << ' ' << b2 << '\n';
  }

}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
