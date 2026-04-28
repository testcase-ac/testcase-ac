#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n; cin >> n;

  ll ans = n * n;
  vector<pii> b;
  for (int i = 0; i < n; i++) {
    int l; cin >> l;
    vector<int> a(l);
    for (int j = 0; j < l; j++) cin >> a[j];
    reverse(a.begin(), a.end());

    if (is_sorted(a.begin(), a.end())) {
      b.emplace_back(a[0], a.back());
    }
  }

  int z = b.size();
  sort(b.begin(), b.end());
  for (int i = 0; i < z; i++) {
    auto [s, e] = b[i];
    auto it = lower_bound(b.begin(), b.end(), pii(e, -1));
    ans -= b.end() - it;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
