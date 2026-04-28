#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int s, m;
  cin >> s >> m;

  if (s <= 1023) cout << "No thanks\n";
  else {
    s -= 1023;
    for (int i = 0; i < 10; i++) {
      if (m & (1 << i)) {
        if (s >= (1 << i)) s -= (1 << i);
      }
    }

    if (s == 0) cout << "Thanks\n";
    else cout << "Impossible\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
