#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  double v0, th, x1, h1, h2;
  cin >> v0 >> th >> x1 >> h1 >> h2;

  double t = x1 / (v0 * cos(th * M_PI / 180));
  double bhgt = v0 * t * sin(th * M_PI / 180) - 9.81 * t * t / 2;
  if (h1 + 1 <= bhgt && bhgt <= h2 - 1) cout << "Safe\n";
  else cout << "Not Safe\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
