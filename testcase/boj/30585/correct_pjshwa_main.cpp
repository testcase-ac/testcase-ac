#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int h, w; cin >> h >> w;
  int tot = h * w, zcnt = 0;
  for (int i = 0; i < h; ++i) {
    string s; cin >> s;
    for (char& c : s) zcnt += c == '0';
  }
  cout << min(tot - zcnt, zcnt) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
