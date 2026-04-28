#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q; cin >> Q;
  vector<int> A;
  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int x; cin >> x;
      if (x == 1) sort(A.begin(), A.end());
      else sort(A.rbegin(), A.rend());
    } else {
      int x, t; cin >> x >> t;
      A.insert(A.begin() + x, t);
    }
  }

  cout << A.size() << '\n';
  if (A.size()) {
    for (int x : A) cout << x << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
