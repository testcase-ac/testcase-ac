#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 0, cur = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    int P1, P2; cin >> P1 >> P2;
    cur += (P1 - P2);
    ans = max(ans, -cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
