#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  for (char c : s) {
    // A, B, E, K, M, H, O, P, C, T, Y, X
    if (c == 'A') cout << "a";
    if (c == 'B') cout << "v";
    if (c == 'E') cout << "ye";
    if (c == 'K') cout << "k";
    if (c == 'M') cout << "m";
    if (c == 'H') cout << "n";
    if (c == 'O') cout << "o";
    if (c == 'P') cout << "r";
    if (c == 'C') cout << "s";
    if (c == 'T') cout << "t";
    if (c == 'Y') cout << "u";
    if (c == 'X') cout << "h";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
