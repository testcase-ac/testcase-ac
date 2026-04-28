#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  ll ans = 0, x;
  for (int i = 0; i < N; ++i) {
    cin >> x; ans += x;
  }
  for (int i = 0; i < M; ++i) {
    cin >> x;
    if (x == 0) continue;
    ans *= x;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
