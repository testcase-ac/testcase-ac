#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, k;
  cin >> n >> k;

  ll all = 0;
  multiset<ll> s;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    all += x;
    s.insert(x);
  }

  while (s.size() && all > k) {
    auto it = s.upper_bound(k);
    if (it == s.begin()) break;

    it--;
    all -= *it;
    k += *it;
    s.erase(it);
  }

  if (all > k) cout << "-1\n";
  else cout << n - s.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
