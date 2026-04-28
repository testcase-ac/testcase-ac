#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const string ds = "UDLR";
const int dx[] = {0, 0, -1, 1};
const int dy[] = {1, -1, 0, 0};

void solve() {
  int mx, my; string s; cin >> mx >> my >> s;
  vector<int> cnt(4, 0);
  for (char c : s) ++cnt[ds.find(c)];

  int p[4]; iota(p, p + 4, 0);
  do {
    int x = 0, y = 0, ok = !(mx == 0 && my == 0);
    for (int i = 0; i < 4; ++i) {
      int t = cnt[p[i]];
      while (t--) {
        x += dx[p[i]]; y += dy[p[i]];
        if (x == mx && y == my) ok = 0;
      }
    }
    if (!ok) continue;
    for (int i = 0; i < 4; ++i) for (int j = 0; j < cnt[p[i]]; ++j) cout << ds[p[i]];
    cout << '\n';
    return;
  } while (next_permutation(p, p + 4));

  cout << "Impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
