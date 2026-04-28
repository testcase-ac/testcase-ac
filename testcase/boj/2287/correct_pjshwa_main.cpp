#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int k, t;
  cin >> k >> t;

  set<ll> u[9];
  int c = k;
  for (int i = 1; i <= 8; i++) {
    u[i].insert(c);
    c = c * 10 + k;
  }

  for (int i = 1; i <= 8; i++) for (int j = 1; i + j <= 8; j++) {
    for (ll e1 : u[i]) for (ll e2 : u[j]) {
      u[i + j].insert(e1 + e2);
      if (e1 != e2) u[i + j].insert(abs(e1 - e2));
      u[i + j].insert(e1 * e2);

      if (e1 > e2) u[i + j].insert(e1 / e2);
      else u[i + j].insert(e2 / e1);
    }
  }

  while (t--) {
    int n;
    cin >> n;

    bool found = false;
    for (int i = 1; i <= 8; i++) {
      if (u[i].count(n)) {
        cout << i << '\n';
        found = true;
        break;
      }
    }

    if (!found) cout << "NO\n";
  }
}
