#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 0; cin >> N;
  vector<int> C(8);
  for (int i = 0; i < N; ++i) {
    int r; cin >> r >> r;
    ans = max(ans, ++C[r - 1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
