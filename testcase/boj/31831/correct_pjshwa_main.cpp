#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, acc = 0, ans = 0; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    acc = max(0, acc + x);
    ans += acc >= M;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
