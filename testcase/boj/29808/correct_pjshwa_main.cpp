#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int S; cin >> S;
  if (S % 4763) return cout << "0\n", void();

  S /= 4763;
  vector<pii> ans;
  for (int d1 = 0; d1 <= 200; d1++) for (int d2 = 0; d2 <= 200; d2++) {
    bool v1 = 508 * d1 + 212 * d2 == S;
    bool v2 = 108 * d1 + 212 * d2 == S;
    bool v3 = 508 * d1 + 305 * d2 == S;
    bool v4 = 108 * d1 + 305 * d2 == S;
    if (v1 || v2 || v3 || v4) {
      ans.emplace_back(d1, d2);
    }
  }

  cout << ans.size() << '\n';
  for (auto& [d1, d2] : ans) cout << d1 << ' ' << d2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
