#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  bool t = true;
  for (int i = 1;; i++) {
    if (N < i) {
      if (t) cout << i - N << '\n';
      else cout << "0\n";
      return;
    }
    N -= i;
    t = !t;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
