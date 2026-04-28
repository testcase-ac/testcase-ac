#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<pii> A(N);
  for (auto& [x, y] : A) cin >> x >> y;

  int ans = 0, acc = 0, pre = 0;
  for (auto& [x, y] : A) {
    pre += y;
    ans = max(ans, pre - acc);
    acc += x;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
