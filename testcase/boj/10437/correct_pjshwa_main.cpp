#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int T, X, Y; cin >> T >> X >> Y;
  cout << T << ' ';

  if (X < Y) cout << "2 " << X << ' ' << Y << '\n';
  else {
    if (X + 2 < 5) return cout << "NO PATH\n", void();

    int e = X + 2, d = e - 1;
    int f = Y + d - 2;
    if (f <= e) return cout << "NO PATH\n", void();

    int dif = min(d - 4, f - e - 1);
    d -= dif, f -= dif;

    cout << "6 1 2 3 " << d << ' ' << e << ' ' << f << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
