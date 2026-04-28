#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 1, l; cin >> N;
  cin >> l;
  for (int i = 1; i < N; i++) {
    int x; cin >> x;
    ans += (l <= x);
    l = x;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
