#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int t[26];
void solve() {
  int n; string s;
  cin >> n >> s;
  for (int i = 0; i < n; i++) t[s[i] - 'A']++;

  char mchar = ' ';
  int mv = 1e9;
  for (char c : string("AGCT")) {
    if (t[c - 'A'] < mv) {
      mv = t[c - 'A'];
      mchar = c;
    }
  }

  cout << t[mchar - 'A'] << '\n';
  for (int i = 0; i < n; i++) cout << mchar;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
