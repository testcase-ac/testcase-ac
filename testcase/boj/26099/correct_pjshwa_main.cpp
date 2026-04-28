#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N; cin >> N;

  ll ans = 0;
  while (N % 5) {
    N -= 3;
    ans++;
  }
  if (N < 0) return cout << "-1\n", void();

  ans += N / 5;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
