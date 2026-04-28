#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<char, char> mapping;
int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  string line; getline(cin, line);
  for (char c : line) cout << mapping[c];
  cout << '\n';
}

int main() {
  fast_io();

  string P[3] = {
    "ejp mysljylc kd kxveddknmc re jsicpdrysi",
    "rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd",
    "de kr kd eoya kw aej tysr re ujdr lkgc jv"
  };
  string U[3] = {
    "our language is impossible to understand",
    "there are twenty six factorial possibilities",
    "so it is okay if you want to just give up"
  };

  mapping[' '] = ' ';
  mapping['z'] = 'q';
  mapping['q'] = 'z';
  for (int t = 0; t < 3; t++) {
    for (int i = 0; i < P[t].size(); i++) {
      mapping[P[t][i]] = U[t][i];
    }
  }

  int t = 1;
  cin >> t; cin.ignore();
  while (t--) solve();
}
