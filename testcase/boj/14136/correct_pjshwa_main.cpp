#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6;
int P[MAXV + 1];

void solve() {
  int N; cin >> N;

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;

    P[x] = max(P[x], 1);
    for (int f = 1; f * f <= x; ++f) {
      if (x % f) continue;
      for (int d : {f, x / f}) {
        if (d == x) continue;
        P[x] = max(P[x], P[d] + 1);
      }
    }
    ans = max(ans, P[x]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
