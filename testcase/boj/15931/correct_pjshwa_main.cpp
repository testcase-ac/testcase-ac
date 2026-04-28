#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  n = 52 - n;

  int minv = 8, maxv = min(8, n / 5);
  for (int c1 = 0; c1 <= 13; c1++) for (int c2 = 0; c2 <= 13; c2++)
  for (int c3 = 0; c3 <= 13; c3++) for (int c4 = 0; c4 <= 13; c4++) {
    if (c1 + c2 + c3 + c4 > 13) continue;
    if (c1 + 2 * c2 + 3 * c3 + 4 * c4 != n) continue;

    int maxp = 0;
    // Number of 4-cards set we will use as 3-cards part of full house
    for (int u = 0; u <= c4; u++) {
      // Number of 3-cards set we will use as 2-cards part of full house
      for (int v = 0; v <= c3; v++) {
        int c3max = c3 + u - v;
        int c2max = c2 + v + 2 * (c4 - u);
        maxp = max(maxp, min(c2max, c3max));
      }
    }

    minv = min(minv, maxp);
  }

  cout << minv << ' ' << maxv << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
