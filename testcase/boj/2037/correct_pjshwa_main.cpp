#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int t[26] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};
int g[26] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8};

void solve() {
  int p, w;
  cin >> p >> w;

  cin.ignore();
  string line;
  getline(cin, line);

  char lastc = 0;
  int ans = 0;
  for (char& c : line) {
    if (c == ' ') {
      ans += p;
      lastc = 0;
    }
    else {
      if (lastc && g[lastc - 'A'] == g[c - 'A']) ans += w;
      ans += p * t[c - 'A'];
      lastc = c;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
