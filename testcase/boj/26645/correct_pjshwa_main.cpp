#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  int mlev = N, ans;
  int up[4] = {8, 4, 2, 1};
  for (int c : {0, 1, 2, 3}) {
    int lim = 210 + c * 10;
    int clev = min(lim, N + up[c]);

    if (mlev <= clev) mlev = clev, ans = c + 1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
