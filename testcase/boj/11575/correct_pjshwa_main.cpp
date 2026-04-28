#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int a, b; string s;
  cin >> a >> b >> s;

  for (char c : s) {
    int o = c - 'A';
    o = (a * o + b) % 26;
    cout << (char)(o + 'A');
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
