#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 2e5, MOD = 1e9 + 7;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;

  vector<ll> B(N + 1);
  for (int i = 1; i <= N; i++) cin >> B[i];

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = i; j <= N; j++) {
      ll smin = B[i], smax = B[i];
      for (int k = i + 1; k <= j; k++) {
        smin = min(smin, B[k]);
        smax = max(smax, B[k]);
      }
      ans = (ans + smax * smin) % MOD;
    }
  }
  cout << ans << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
