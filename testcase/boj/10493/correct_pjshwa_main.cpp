#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ld INF = 1e18;
ld B[4], T[4], D[4];

void solve() {
  for (int i = 0; i < 4; i++) D[i] = T[i] - B[i];

  vector<ld> cps{0, 1};
  if (D[2] * D[2] >= 3 * D[1] * D[3]) {
    ld Q = sqrt(D[2] * D[2] - 3 * D[1] * D[3]);
    for (ld c : {(-1 * D[2] + Q) / (3 * D[3]), (-1 * D[2] - Q) / (3 * D[3])}) {
      if (c >= 0 && c <= 1) cps.push_back(c);
    }
  }

  ld maxd = -INF, mind = INF;
  for (ld c : cps) {
    ld Bc = B[3] * c * c * c + B[2] * c * c + B[1] * c + B[0];
    ld Tc = T[3] * c * c * c + T[2] * c * c + T[1] * c + T[0];

    maxd = max(maxd, Tc - Bc);
    mind = min(mind, Tc - Bc);
  }
  cout << fixed << setprecision(10) << maxd - mind << '\n';
}

int main() {
  fast_io();

  while (
    cin >> B[0] >> B[1] >> B[2] >> B[3] >>
    T[0] >> T[1] >> T[2] >> T[3]
  ) solve();
}
