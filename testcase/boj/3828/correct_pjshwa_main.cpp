#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXD = 5;
int d;
ld f[MAXD + 5];

bool check(vector<pair<ld, ld>>& pts) {

  for (auto& [xp, yp] : pts) {

    ld val = 0;
    for (int i = 0; i <= d; ++i) {
      auto [xi, yi] = pts[i];
      ld num = yi, den = 1;

      for (int j = 0; j <= d; ++j) {
        if (i == j) continue;

        auto [xj, yj] = pts[j];
        num *= (xp - xj);
        den *= (xi - xj);
      }

      val += num / den;
    }

    if (abs(yp - val) > 0.5) return false;
  }

  return true;
}

void solve() {
  for (int i = 0; i <= d + 2; ++i) cin >> f[i];
  for (int i = 0; i <= d + 2; ++i) {
    vector<pair<ld, ld>> pts;
    for (int j = 0; j <= d + 2; ++j) {
      if (i == j) continue;
      pts.emplace_back(j, f[j]);
    }
    if (check(pts)) {
      cout << i << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  while (cin >> d) {
    if (d == 0) break;
    solve();
  }
}
