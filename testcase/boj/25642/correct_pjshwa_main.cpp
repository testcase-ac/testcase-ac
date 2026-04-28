#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B;
  cin >> A >> B;

  bool f = true;
  while (1) {
    if (f) {
      if (A + B >= 5) return cout << "yt\n", void();
      B += A;
    }
    else {
      if (A + B >= 5) return cout << "yj\n", void();
      A += B;
    }
    f = !f;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
