#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pll H[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> H[i].first;
  for (int i = 1; i <= N; i++) cin >> H[i].second;
  sort(H + 1, H + N + 1, [] (const pll& a, const pll& b) {
    return a.second < b.second;
  });

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    auto [h, a] = H[i];
    ans += h + a * (i - 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
