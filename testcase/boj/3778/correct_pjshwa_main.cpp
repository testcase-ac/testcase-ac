#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int st[26], tt[26];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  string s, t;
  getline(cin, s); getline(cin, t);

  memset(st, 0, sizeof(st));
  memset(tt, 0, sizeof(tt));

  for (char& c : s) st[c - 'a']++;
  for (char& c : t) tt[c - 'a']++;

  int ans = 0;
  for (int i = 0; i < 26; i++) {
    ans += abs(st[i] - tt[i]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  cin.ignore();
  while (t--) solve();
}
