#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  map<int, int> d;
  for (int i = 0; i < n; i++) {
    int k, v;
    cin >> k >> v;
    d[k] = v;
  }

  while (m--) {
    int op, a, b;
    cin >> op;
    if (op == 1) {
      cin >> a >> b;
      d[a] = b;
    }
    if (op == 2) {
      cin >> a >> b;
      auto it = d.lower_bound(a);
      if (it == d.begin() && abs(a - it->first) <= k) d[it->first] = b;
      else {
        auto it2 = it;
        it2--;
        if (abs(a - it->first) < abs(a - it2->first)) {
          if (abs(a - it->first) <= k) d[it->first] = b;
        }
        else if (abs(a - it->first) > abs(a - it2->first)) {
          if (abs(a - it2->first) <= k) d[it2->first] = b;
        }
      }
    }
    if (op == 3) {
      cin >> a;
      auto it = d.lower_bound(a);
      if (it == d.begin()) {
        if (abs(a - it->first) <= k) cout << d[it->first] << '\n';
        else cout << "-1\n";
      }
      else {
        auto it2 = it;
        it2--;
        if (abs(a - it->first) < abs(a - it2->first)) {
          if (abs(a - it->first) <= k) cout << d[it->first] << '\n';
          else cout << "-1\n";
        }
        else if (abs(a - it->first) > abs(a - it2->first)) {
          if (abs(a - it2->first) <= k) cout << d[it2->first] << '\n';
          else cout << "-1\n";
        }
        else cout << "?\n";
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
