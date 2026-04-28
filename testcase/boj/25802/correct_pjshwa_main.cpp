#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B;
  cin >> A >> B;

  int a = A, b = B;
  for (int it = 3;; it++) {
    int t = (a + b) % 10;
    a = b, b = t;
    if (a == A && b == B) {
      cout << it << '\n';
      break;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
