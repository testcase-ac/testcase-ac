#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll A[MAXN + 1], P[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i], P[i] = P[i - 1] + A[i];

  ll ans = A[1];
  for (int i = 2; i <= N; ++i) ans = max(ans, A[i] - P[i - 1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
