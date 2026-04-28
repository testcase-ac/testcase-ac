#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int src[MAX + 1], des[MAX + 1], dcopy[MAX + 1], tc;

void solve() {
  cout << "Case #" << ++tc << ": ";

  int n, a, b;
  cin >> n >> a >> b;
  memset(des, 0, sizeof(des));
  for (int i = 1; i <= n; i++) cin >> des[i];

  for (int i = 1; i <= 500; i++) {
    memset(src, 0, sizeof(src));

    int mval = i;
    src[i] = 1;

    for (int j = 1; j <= n; j++) dcopy[j] = des[j];

    while (1) {
      for (int j = 1; j <= n; j++) {
        int use = min(src[j], dcopy[j]);
        src[j] -= use, dcopy[j] -= use;
      }

      int u = src[mval];
      src[mval] = 0;
      if (mval - a >= 1) src[mval - a] = min(src[mval - a] + u, 1'000'000);
      if (mval - b >= 1) src[mval - b] = min(src[mval - b] + u, 1'000'000);

      while (mval >= 1 && src[mval] == 0) mval--;
      if (mval == 0) break;
    }

    bool azero = true;
    for (int j = 1; j <= n; j++) azero &= (dcopy[j] == 0);
    if (azero) {
      cout << i << '\n';
      return;
    }
  }

  cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
