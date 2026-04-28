#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int g, k, l;
  string s, t;
  cin >> g >> k >> l;

  while (g--) {
    cin >> l >> s >> l >> t;
    if (k == 1 || s.size() <= t.size()) cout << 'Y';
    if (k == 1 || s.size() >= t.size()) cout << 'S';
    cout << '\n';
  }
}
