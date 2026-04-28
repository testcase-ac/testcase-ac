#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll X[MAXN + 1], P[MAXN + 1];

void solve() {
  ll N, L, B; cin >> N >> L >> B;
  for (int i = 1; i <= N; ++i) cin >> X[i], P[i] = P[i - 1] + X[i];

  int ans = 0;
  for (int l = 1; l <= N; ++l) {
    int left = l, right = N + 1;
    while (left < right) {
      int mid = (left + right) / 2;

      // cost to cover [l, mid] ?
      int midp = (l + mid) / 2;
      ll cost = P[mid] - P[midp] - (mid - midp) * X[midp];
      cost += (midp - l + 1) * X[midp] - (P[midp] - P[l - 1]);

      if (cost <= B) left = mid + 1;
      else right = mid;
    }
    ans = max(ans, left - l);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
