#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N; N -= 10;

  ll ans = 6;
  for (int i = 0; i < N; i++) ans *= (i + 11);
  cout << ans << '\n';
}

int main() {
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
