#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int x, b; cin >> x >> b;
  if (x == 0) return cout << "0\n", void();

  if (x < 0 && b > 0) cout << '-', x = -x;
  vector<int> ans;
  while (x) {
    if (x % b < 0) {
      ans.push_back(x % b - b);
      x = x / b + 1;
    } else {
      ans.push_back(x % b);
      x /= b;
    }
  }
  while (!ans.empty()) cout << ans.back(), ans.pop_back();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
