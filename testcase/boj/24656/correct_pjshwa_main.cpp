#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    int a, b; cin >> a >> b;

    if (b & 1) ans ^= (a & 1);
    else {
      int m = a % (b + 1);
      if (m == b) ans ^= 2;
      else ans ^= (m & 1);
    }
  }

  if (ans == 0) cout << "Bob\n";
  else cout << "Alice\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
