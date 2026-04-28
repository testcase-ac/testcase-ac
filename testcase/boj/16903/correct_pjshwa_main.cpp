#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

multiset<uint> s0{0};

uint find_max(uint v) {
  uint ans = 0;
  for (int b = 30; b >= 0; b--) {
    if (v & (1U << b)) {
      uint bn = ans;
      uint lb = bn, ub = bn + (1U << b);
      if (s0.lower_bound(lb) == s0.lower_bound(ub)) ans |= (1U << b);
    }
    else {
      uint bn = ans | (1U << b);
      uint lb = bn, ub = bn + (1U << b);
      if (s0.lower_bound(lb) != s0.lower_bound(ub)) ans |= (1U << b);
    }
  }
  return v ^ ans;
}

void solve() {
  int q;
  cin >> q;

  while (q--) {
    uint op, v;
    cin >> op >> v;

    if (op == 1) s0.insert(v);
    if (op == 2) s0.erase(s0.find(v));
    if (op == 3) cout << find_max(v) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
