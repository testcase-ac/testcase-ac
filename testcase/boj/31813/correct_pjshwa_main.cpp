#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, K; cin >> N >> K;

  vector<ll> ans;
  while (K) {
    for (int d = 17; d >= 1; --d) {
      bool f = false;
      for (char c = '9'; c >= '1'; --c) {
        string O;
        for (int i = 0; i < d; ++i) O += c;
        ll Ol = stoll(O);
        if (Ol <= K) {
          f = true;
          ans.push_back(Ol);
          K -= Ol;
          break;
        }
      }
      if (f) break;
    }
  }

  cout << ans.size() << '\n';
  for (ll e : ans) cout << e << ' '; cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
