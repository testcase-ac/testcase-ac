#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

set<int> s0;

int find_min(int v) {
  int ans = 0;
  for (int b = 24; b >= 0; b--) {
    if (v & (1 << b)) {
      int bn = ans | (1 << b);
      int lb = bn, ub = bn + (1 << b);
      if (s0.lower_bound(lb) != s0.lower_bound(ub)) ans |= (1 << b);
    }
    else {
      int bn = ans;
      int lb = bn, ub = bn + (1 << b);
      if (s0.lower_bound(lb) == s0.lower_bound(ub)) ans |= (1 << b);
    }
  }
  return v ^ ans;
}

int find_max(int v) {
  int ans = 0;
  for (int b = 24; b >= 0; b--) {
    if (v & (1 << b)) {
      int bn = ans;
      int lb = bn, ub = bn + (1 << b);
      if (s0.lower_bound(lb) == s0.lower_bound(ub)) ans |= (1 << b);
    }
    else {
      int bn = ans | (1 << b);
      int lb = bn, ub = bn + (1 << b);
      if (s0.lower_bound(lb) != s0.lower_bound(ub)) ans |= (1 << b);
    }
  }
  return v ^ ans;
}

void solve() {
  int n, q;
  cin >> n >> q;

  s0.clear();
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    s0.insert(x);
  }

  while (q--) {
    int op, v;
    cin >> op;
    if (1 <= op && op <= 3) cin >> v;

    if (op == 1) cout << find_min(v) << '\n';
    if (op == 2) cout << find_max(v) << '\n';
    if (op == 3) s0.insert(v), cout << s0.size() << '\n';
    if (op == 4) cout << *s0.begin() << '\n', s0.erase(s0.begin());
    if (op == 5) {
      auto it = s0.end();
      it--;
      cout << *it << '\n', s0.erase(it);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
