#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<pair<ll, int>> odds, evens;
  for (int i = 0; i < N; ++i) {
    ll x; cin >> x;
    if (x & 1) odds.emplace_back(x, i);
    else evens.emplace_back(x, i);
  }

  vector<int> res(N);
  for (auto& [_, i] : odds) res[i] = 1;

  sort(evens.begin(), evens.end());
  ll g = 1, lb = 0;
  for (auto& [x, i] : evens) {
    if (x >= lb) ++g, lb = 2 * x;
    res[i] = g;
  }

  for (int i = 0; i < N; ++i) cout << res[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
