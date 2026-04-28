#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, D;
  cin >> N >> D;

  map<int, ll> T;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    T[-x]++;
  }

  ll ans = 0;
  while (D--) {
    auto [x, c] = *T.begin();
    // cout << "x: " << x << " c: " << c << endl;

    if (x == 0) break;

    ans += c;
    T.erase(x);
    T[x + 1] += c;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
