#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int d, x, s; cin >> d >> x >> s;

  int cx = 0, cs = 0;
  int cpl = INT_MAX, cps = INT_MAX;

  int cost = 0;
  for (int i = 0; i < d; ++i) {
    int c, pl, ps; cin >> c >> pl >> ps;
    cpl = min(cpl, pl); cps = min(cps, ps);

    int xneed = max(0, c * x - cx), bneed = max(0, (c * s - cs + 79) / 80);
    cost += xneed * cpl + bneed * cps;
    cx += xneed; cs += bneed * 80;
    cx -= c * x; cs -= c * s;
  }

  cout << cost << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
