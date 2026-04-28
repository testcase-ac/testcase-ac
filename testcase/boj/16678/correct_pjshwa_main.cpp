#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  map<int, int> spare;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    spare[x]++;
  }

  ll cnt = 0, ans = 0;
  for (int i = 1;; i++) {
    if (spare.count(i)) {
      cnt += spare[i];
      spare.erase(i);
    }
    else {
      auto it = spare.lower_bound(i);
      auto& [v, t] = *it;
      ans += v - i;
      t--;
      if (t == 0) spare.erase(it);
      cnt++;
    }
    if (spare.empty()) break;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
