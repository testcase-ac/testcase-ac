#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  string s;
  map<char, int> t;
  while (cin >> s) {
    for (char c : s) {
      if (t.count(c)) t[c]++;
      else t[c] = 1;
    }
  }

  int mval = 0;
  for (auto [c, v] : t) {
    if (v > mval) mval = v;
  }

  for (auto [c, v] : t) {
    if (v == mval) cout << c;
  }
  cout << '\n';
}
