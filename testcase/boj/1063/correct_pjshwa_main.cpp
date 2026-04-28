#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string k, r;
  int m;
  cin >> k >> r >> m;

  int ci = 8 - (k[1] - '0'), cj = k[0] - 'A';
  int ri = 8 - (r[1] - '0'), rj = r[0] - 'A';
  while (m--) {
    string op;
    cin >> op;

    int ni, nj;
    if (op == "R") ni = ci, nj = cj + 1;
    if (op == "L") ni = ci, nj = cj - 1;
    if (op == "B") ni = ci + 1, nj = cj;
    if (op == "T") ni = ci - 1, nj = cj;
    if (op == "RT") ni = ci - 1, nj = cj + 1;
    if (op == "LT") ni = ci - 1, nj = cj - 1;
    if (op == "RB") ni = ci + 1, nj = cj + 1;
    if (op == "LB") ni = ci + 1, nj = cj - 1;

    if (ni < 0 || ni > 7 || nj < 0 || nj > 7) continue;
    if (ni == ri && nj == rj) {
      int nri = ni + (ni - ci), nrj = nj + (nj - cj);
      if (nri < 0 || nri > 7 || nrj < 0 || nrj > 7) continue;
      ri = nri, rj = nrj;
    }
    ci = ni, cj = nj;
  }

  cout << (char)('A' + cj) << (char)('8' - ci) << '\n';
  cout << (char)('A' + rj) << (char)('8' - ri) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
