#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  map<int, ll> by_d;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int x; cin >> x;
    by_d[j - i] += x;
  }

  ll ans = 0;
  for (auto& [_, sum] : by_d) ans = max(ans, sum);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
