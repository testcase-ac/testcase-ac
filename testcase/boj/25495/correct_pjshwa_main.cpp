#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;

  int cum = 0, luse = -1, last = -1;
  for (int i = 0, x; i < N; i++) {
    cin >> x;

    int cuse;
    if (last == x) cuse = luse * 2;
    else cuse = 2;

    cum += cuse;
    luse = cuse;
    last = x;

    if (cum >= 100) {
      cum = 0;
      luse = -1;
      last = -1;
    }
  }

  cout << cum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
