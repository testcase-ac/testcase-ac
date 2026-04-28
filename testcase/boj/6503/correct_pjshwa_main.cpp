#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int m;
string s;

unordered_map<int, int> in;
int inc;

void inc_update(int x, int diff) {
  if (diff < 0 && in[x] == 1) inc--;
  if (diff > 0 && in[x] == 0) inc++;
  in[x] += diff;
}

void solve() {
  int n = s.size(), ans = 0, ep = 0;
  for (int sp = 0; sp < n; sp++) {
    while (ep < n && inc <= m) {
      ans = max(ans, ep - sp);
      inc_update(s[ep], 1);
      ep++;
    }
    if (inc <= m) ans = max(ans, ep - sp);

    inc_update(s[sp], -1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> m;
    if (m == 0) break;
    cin.ignore();
    getline(cin, s);
    solve();
  }
}
