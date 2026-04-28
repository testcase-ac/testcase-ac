#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int D[MAXN + 1];

void solve() {
  int n, k, T; cin >> n >> k >> T;
  for (int i = 1; i <= n; ++i) cin >> D[i];

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (T > k) T = T + D[i] - abs(T - k);
    else if (T < k) T = T + D[i] + abs(T - k);
    else T += D[i];
    ans += abs(T - k);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
