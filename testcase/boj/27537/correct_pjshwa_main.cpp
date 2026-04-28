#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int x, e; cin >> x >> e;
    A.push_back({x - e, x + e});
  }
  sort(A.begin(), A.end());

  map<int, int> by_s;
  for (auto& [s, e] : A) by_s[s] = e;

  int ans = 0, maxr = INT_MIN;
  for (auto [s, e] : by_s) {
    if (e > maxr) {
      ++ans;
      maxr = e;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
