#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int b[6];
  for (int i = 1; i <= 5; ++i) cin >> b[i];

  int ans = 0;
  for (int q1 = 0; q1 <= 15; q1++) for (int q2 = 0; q2 <= 15; q2++) for (int q3 = 0; q3 <= 15; q3++)
  for (int q4 = 0; q4 <= 15; q4++) for (int q5 = 0; q5 <= 15; q5++) {
    int s = q1 + q2 + q3 + q4 + q5;
    int ws = 1 * q1 + 2 * q2 + 3 * q3 + 4 * q4 + 5 * q5;
    if (s <= 3) {
      if (ws > 10) continue;
    }
    else {
      if (ws > 15) continue;
    }

    int cost = b[1] * q1 + b[2] * q2 + b[3] * q3 + b[4] * q4 + b[5] * q5;
    ans = max(ans, cost);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
