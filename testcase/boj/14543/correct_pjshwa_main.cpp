#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Equation " << ++tc << "\n";
  string ls, op;
  ll l, r, t;
  cin >> ls >> op >> r >> op >> t;
  t -= r;

  l = stoi(ls.substr(0, ls.size() - 1));
  if (l == 0) {
    if (t == 0) cout << "More than one solution.\n";
    else cout << "No solution.\n";
  }
  else {
    ll rint = t * 1'000'000 / l;
    double res = rint / 1'000'000.0;
    cout << "x = " << fixed << setprecision(6) << res << "\n";
  }

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
