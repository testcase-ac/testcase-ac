#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, K; cin >> N >> K;
  ll S = 0, QS = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    S += x; QS += x * x;
  }
  ll P = (S * S - QS) / 2;

  if (P == 0) cout << "0\n";
  else if (S && P % S == 0) cout << -P / S << '\n';
  else if (K >= 2) {
    ll x1 = 1 - S, x2 = S * S - P - S;
    cout << x1 << ' ' << x2 << '\n';
  }
  else cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
