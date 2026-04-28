#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S;
  cin >> N >> S;

  int hc = 0, ic = 0, ac = 0, rc = 0, cc = 0;
  for (char& c : S) {
    if (c == 'H') hc++;
    if (c == 'I') ic++;
    if (c == 'A') ac++;
    if (c == 'R') rc++;
    if (c == 'C') cc++;
  }
  cout << min({hc, ic, ac, rc, cc}) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
