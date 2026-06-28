#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int Q;
  cin >> Q;

  vector<pll> as;
  while (Q--) {
    int op;
    cin >> op;
    if (op == 1) {
      ll a, b;
      cin >> a >> b;
      as.push_back({a, b});
    }
    if (op == 2) {
      ll x;
      cin >> x;

      ll res = 1;
      for (auto& [a, b] : as) {
        res *= (a * x + b);
      }

      if (res > 0) cout << "+\n";
      else if (res == 0) cout << "0\n";
      else cout << "-\n";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
