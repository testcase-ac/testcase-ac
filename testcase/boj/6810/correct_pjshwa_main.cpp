#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int s = 91;
  for (int i = 0, x; i < 3; i++) {
    cin >> x;
    if (i & 1) s += x * 3;
    else s += x;
  }

  cout << "The 1-3-sum is " << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
