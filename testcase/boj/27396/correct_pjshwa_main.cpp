#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int c2i(char c) {
  if (c >= 'a' && c <= 'z') return c - 'a';
  return c - 'A' + 26;
}

char i2c(int i) {
  if (i < 26) return i + 'a';
  return i - 26 + 'A';
}

void solve() {
  string S; int Q; cin >> S >> Q;

  int map[52]; iota(map, map + 52, 0);
  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      string s1, s2; cin >> s1 >> s2;
      int i1 = c2i(s1[0]), i2 = c2i(s2[0]);
      for (auto& v : map) if (v == i1) v = i2;
    }
    if (op == 2) {
      for (char c : S) cout << i2c(map[c2i(c)]);
      cout << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
