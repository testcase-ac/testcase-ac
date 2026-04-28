#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int p[5] = {0};
  p[1] = 1, p[4] = 2;

  for (char& c : s) {
    if (c == 'A') swap(p[1], p[2]);
    if (c == 'B') swap(p[1], p[3]);
    if (c == 'C') swap(p[1], p[4]);
    if (c == 'D') swap(p[2], p[3]);
    if (c == 'E') swap(p[2], p[4]);
    if (c == 'F') swap(p[3], p[4]);
  }

  for (int i = 1; i <= 4; i++) if (p[i] == 1) cout << i << '\n';
  for (int i = 1; i <= 4; i++) if (p[i] == 2) cout << i << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
