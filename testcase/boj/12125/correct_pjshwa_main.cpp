#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;
void solve_M1() {
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (x > 0) ans += x;
  }
  cout << ans << '\n';
}

void solve_M2() {
  int ans = 0;

  int xgain = 0, xnet = 0, ygain = 0, ynet = 0;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    if (x <= 0 && y <= 0) continue;

    if (x > 0 && y > 0) ans += x + y;
    else if (x > 0) {
      xgain += x;
      if (x + y > 0) xnet += x + y;
    }
    else {
      ygain += y;
      if (x + y > 0) ynet += x + y;
    }
  }

  int profit = max(xgain + ynet, ygain + xnet);
  cout << ans + profit << '\n';
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int M; cin >> N >> M;
  if (M == 1) solve_M1();
  else solve_M2();
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
