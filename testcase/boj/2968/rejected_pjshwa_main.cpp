#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int R, C;
  ll K, ans = 0, s = 0;
  cin >> R >> C >> K;

  for (int i = 1; i <= R + C; i++) {
    int addend = min({i, R, C, R + C - i});

    if (s + addend >= K) {
      for (int u = 0; u < R; u++) {
        int cmax = min(C, max(0, i - 1 - u));
        if (cmax == 0) break;

        // Count numbers x from 0 to cmax - 1, where u & x == 0
        stack<int> bits;
        int t = cmax - 1;
        for (int b = 20; b >= 0; b--) {
          int m = (1 << b);
          if (u & m) continue;

          if (m <= t) {
            t -= m;
            bits.push(1);
          }
          else bits.push(0);
        }

        ll pw = 1;
        while (!bits.empty()) {
          ans += bits.top() * pw;
          bits.pop();
          pw *= 2;
        }
        ans++;

      }

      int rl = min(R, i), cl = max(0, i - R);
      for (int j = 0; j < K - s; j++) {
        int b;
        if (i & 1) b = rl - 1 - j;
        else b = cl + j;

        if (b & (i - 1 - b)) continue;
        ans++;
      }
      break;
    }

    s += addend;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
