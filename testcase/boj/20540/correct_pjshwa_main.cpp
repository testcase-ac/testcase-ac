#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char inv(char c) {
  if (c == 'E') return 'I';
  if (c == 'I') return 'E';
  if (c == 'S') return 'N';
  if (c == 'N') return 'S';
  if (c == 'T') return 'F';
  if (c == 'F') return 'T';
  if (c == 'J') return 'P';
  if (c == 'P') return 'J';
}

void solve() {
  string S;
  cin >> S;
  for (char c : S) cout << inv(c);
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
