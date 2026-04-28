#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;

  int p1 = 0, p2 = 0;
  for (char c : S) {
    if (c == 'U' || c == 'C') p1++;
    if (c == 'D' || c == 'P') p2++;
  }

  bool uu = false, ud = false, up = false;
  for (int d = 0; d <= p2; d++) {
    int p = p2 - d;

    if (p1 > max(d, p)) uu = true;
    if (d > p) ud = true;
    if (p > d) up = true;
  }

  if (!uu && !ud && !up) cout << "C\n";
  else {
    if (uu) cout << 'U';
    if (ud) cout << 'D';
    if (up) cout << 'P';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
