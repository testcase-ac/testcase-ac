#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int d[MAX];

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  int cc = 0, oc = 0, wc = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'C') cc ^= 1;
    if (s[i] == 'O') oc ^= 1;
    if (s[i] == 'W') wc ^= 1;

    d[i] = cc * 4 + oc * 2 + wc;
  }

  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    x--; y--;

    int a = d[y];
    if (x) a ^= d[x - 1];

    if (a == 3 || a == 4) cout << 'Y';
    else cout << 'N';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
