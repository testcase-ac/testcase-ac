#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll f(ll n) {
  if (n == 0) return 0;
  return f(n / 2) + n;
}

void solve() {
  ll N; cin >> N;
  cout << f(N) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
