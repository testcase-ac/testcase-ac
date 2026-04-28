#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N; cin >> N;

  vector<pair<ll, ll>> candidates;
  ll l = 0, r = 0, sum = 0;
  while (r * r <= N) {
    if (sum < N) {
      ++r; sum += r * r;
    } else {
      ++l; sum -= l * l;
    }
    if (sum == N) candidates.emplace_back(l + 1, r);
  }

  cout << candidates.size() << '\n';
  for (auto& [l, r] : candidates) {
    cout << r - l + 1 << ' ';
    for (ll i = l; i <= r; ++i) cout << ' ' << i;
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
