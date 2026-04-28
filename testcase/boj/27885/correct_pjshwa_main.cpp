#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 86400;
int U[MAX];

int s2t(string str) {
  int h = stoi(str.substr(0, 2));
  int m = stoi(str.substr(3, 2));
  int s = stoi(str.substr(6, 2));
  return h * 3600 + m * 60 + s;
}

void solve() {
  int c, h; cin >> c >> h; c += h;
  while (c--) {
    string str; cin >> str;
    int s = s2t(str);
    for (int j = s; j < s + 40; j++) U[j] = 1;
  }

  int ans = MAX;
  for (int j = 0; j < MAX; j++) ans -= U[j];
  cout << ans << '\n';
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
