#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll r, a, b;
  cin >> r >> a >> b;

  ll sum = 0;
  while (r) {
    sum += r * r;
    r *= a;
    sum += r * r;
    r /= b;
  }

  cout << fixed << setprecision(10) << M_PI * sum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
