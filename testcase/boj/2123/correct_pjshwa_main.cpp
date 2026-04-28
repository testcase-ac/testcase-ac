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
    int w, s; cin >> w >> s;
    A.emplace_back(w + s, w);
  }
  sort(A.begin(), A.end());

  ll sum = 0, ans = -1e18;
  for (auto& [tot, wgt] : A) {
    ans = max(ans, sum - (tot - wgt));
    sum += wgt;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
